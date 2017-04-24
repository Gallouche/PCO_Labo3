#include "locomotive.h"
#include "ctrain_handler.h"

Locomotive::Locomotive() :
    _numero(-1),
    _vitesse(0),
    _enFonction(false),
    _priorite(-1),
    _sens(AVANT)
{}

Locomotive::Locomotive(int numero, int vitesse, QList<int> parcours,
                       int priorite) :
    _numero(numero),
    _vitesse(vitesse),
    _enFonction(false),
    _priorite(priorite),
    _parcours(parcours),
    _sens(AVANT)
{}

void Locomotive::run(){
    fixerPosition(_parcours.at(0),_parcours.at(_parcours.size()-1));
    allumerPhares();
    afficherMessage("Ready!");

    for(int i = 1; i < _parcours.size(); i++){
        attendre_contact(_parcours.at(i));
        afficherMessage(QString("I've reached contact no. %1.").arg(_parcours.at(i)));
    }
    arreter();
    afficherMessage("I'm done!");
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
