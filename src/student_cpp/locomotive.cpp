/**
 * -------------------------------------------------------------------------------
 * Laboratoire : PCO - Labo3
 * Fichier     : locomotive.cpp
 * Auteur(s)   : Théo Gallandat & Kevin Moreira
 * Date        : 24/04/2017
 *
 * But         : Implémentation de la classe Locomotive
 *
 * Remarque(s) : Modification du code source fourni pour la labo
 -------------------------------------------------------------------------------
 */

#include "locomotive.h"
#include "ctrain_handler.h"
#include "tronconcritique.h"

//Constructeur par défaut
Locomotive::Locomotive() :
    _aiguillages(),
    _numero(-1),
    _vitesse(0),
    _enFonction(false),
    _sens(AVANT),
    _parcours()
{}

//Constructeur
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

//Destructeur
Locomotive::~Locomotive(){
    for(Aiguillage* a : _aiguillages){
        delete a;
    }
}

//fonction run appeler au start du thread
void Locomotive::run(){
    while (true) {
        //compteur du nombres de tours (2 dans chaque sens infiniment)
        int nbtours = 0;
        //Bool présence d'une loco sur le troncon critique.
        bool inTronconCo = false;
        //phase de sortie du troncon
        bool sortie = false;
        //phase d'entree sur le troncon
        bool entree = false;

        while (nbtours < 2) {
            for(int i = 0; i < _parcours.size(); i++){
                int contactCurrent = _parcours.at(i);

                /**
                 * Si la loco n'est pas sur le troncon, que le le prochaine contact n'est pas
                 * le dernier de la liste et que c'est une entrée d'un troncon, on demande
                 * le troncon.
                 */

                if(!inTronconCo && ((i+1) < _parcours.size()) &&
                        TronconCritique::tronconCritique->bordTroncon(_parcours.at(i+1))){
                    afficherMessage("inscription");
                    TronconCritique::tronconCritique->demandeTroncon(this);
                }

                //Si le contact courrant est une entree du troncon critique,
                if(TronconCritique::tronconCritique->bordTroncon(contactCurrent)){

                    //si l'on est pas déja dans le troncon.
                    if(!inTronconCo){
                        afficherMessage("reservation");
                        //on réquisitionnne le troncon
                        TronconCritique::tronconCritique->bloqueTroncon(this);
                        afficherMessage("entre dans le troncon");
                        entree = true;
                    }
                    //sinon c'est qu'on en sort.
                    else{
                        afficherMessage("sortie du troncon");
                        sortie = true;
                    }
                }
                /**
                  * Ici on regarde si le contact sur lequel on est est sencé faire
                  * bouger un aiguillage et si c'est le cas on le fait.
                  */
                for(Aiguillage* a : _aiguillages){
                    if(a->getContactDecl() == contactCurrent && a->getSens() == _sens){
                        diriger_aiguillage(a->getNum(),a->getDirection(),0);
                    }
                }

                attendre_contact(contactCurrent);

                //On termine la phase d'entree
                if(entree){
                    inTronconCo = true;
                    entree = false;
                }

                //si on est en sortie
                if(sortie){
                    inTronconCo = false;
                    // on libère le troncon critique.
                    TronconCritique::tronconCritique->libererTroncon(this);
                    sortie = false;
                    afficherMessage("troncon liberer");
                }

                afficherMessage(QString("I've reached contact no. %1.").arg(_parcours.at(i)));
            }
            nbtours++;
        }
        //on inverse le parcours et le sens de la locomotive et on recommence.
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
