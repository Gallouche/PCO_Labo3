#include "locomotive.h"
#include "ctrain_handler.h"
#include "tronconcritique.h"

Locomotive::Locomotive() :
    _aiguillages(),
    _numero(-1),
    _vitesse(0),
    _enFonction(false),
    _sens(AVANT),
    _parcours()
{}

Locomotive::Locomotive(int numero, int vitesse, QList<int> parcours,
                       int priorite, QList<Aiguillage*> aiguillages) :
    _numero(numero),
    _vitesse(vitesse),
    _enFonction(false),
    _priorite(priorite),
    _parcours(parcours),
    _sens(AVANT),
    _aiguillages(aiguillages)
{}

Locomotive::~Locomotive(){
    for(Aiguillage* a : _aiguillages){
        delete a;
    }
}

void Locomotive::run(){
    while (true) {
        int nbtours = 0;
        bool inTronconCo = false;
        bool sortie = false;
        bool entree = false;

        while (nbtours < 2) {
            for(int i = 0; i < _parcours.size(); i++){
                int contactCurrent = _parcours.at(i);
                if(!inTronconCo && ((i+1) < _parcours.size()) &&
                        TronconCritique::tronconCritique->bordTroncon(_parcours.at(i+1))){
                    afficherMessage("inscription");
                    TronconCritique::tronconCritique->demandeTroncon(this);
                }
                if(TronconCritique::tronconCritique->bordTroncon(contactCurrent)){
                    if(!inTronconCo){
                        afficherMessage("reservation");
                        TronconCritique::tronconCritique->bloqueTroncon(this);
                        afficherMessage("entre dans le troncon");
                        entree = true;
                    }
                    else{
                        afficherMessage("sortie du troncon");
                        sortie = true;
                    }
                }
                for(Aiguillage* a : _aiguillages){
                    if(a->getContactDecl() == contactCurrent && a->getSens() == _sens){
                        afficherMessage("Changement aiguillage: " + a->getNum());
                        diriger_aiguillage(a->getNum(),a->getDirection(),0);
                    }
                }
                attendre_contact(contactCurrent);
                if(entree){
                    inTronconCo = true;
                    entree = false;
                }
                if(sortie){
                    inTronconCo = false;
                    TronconCritique::tronconCritique->libererTroncon(this);
                    sortie = true;
                    afficherMessage("troncon liberer");
                }
                afficherMessage(QString("I've reached contact no. %1.").arg(_parcours.at(i)));
            }
            nbtours++;
        }
        std::reverse(_parcours.begin(),_parcours.end());
        inverserSens();
    }
}

int Locomotive::numero() const
{
    return _numero;
}

void Locomotive::fixerNumero(int numero)
{
    _numero = numero;
}

int Locomotive::vitesse() const
{
    return _vitesse;
}

void Locomotive::fixerVitesse(int vitesse)
{
    _vitesse = vitesse;

    if (_enFonction)
        mettre_vitesse_progressive(_numero, vitesse);
}

void Locomotive::fixerPosition(int contactAvant, int contactArriere)
{
    assigner_loco(contactAvant, contactArriere, _numero, _vitesse);
}

void Locomotive::afficherMessage(const QString &message)
{
    afficher_message_loco(_numero, qPrintable(message));
}

void Locomotive::allumerPhares()
{
    mettre_fonction_loco(_numero, ALLUME);
}

void Locomotive::eteindrePhares()
{
    mettre_fonction_loco(_numero, ETEINT);
}

void Locomotive::demarrer()
{
    mettre_vitesse_progressive(_numero, _vitesse);
    _enFonction = true;
}

void Locomotive::arreter()
{
    arreter_loco(_numero);
    _enFonction = false;
}

void Locomotive::inverserSens()
{
    inverser_sens_loco(_numero);
    _sens = !_sens;
}

void Locomotive::fixerPriorite(int priorite){
    _priorite = priorite;
}

int Locomotive::getPriorite(){
    return _priorite;
}
