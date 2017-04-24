#include "ctrain_handler.h"
#include "locomotive.h"
#include "tronconcritique.h"

#include <QList>

//déclaration des locomotives
Locomotive* locomotive1;
Locomotive* locomotive2;

//Arret d'urgence
void emergency_stop()
{
    locomotive1->arreter();
    locomotive2->arreter();
    afficher_message("\nSTOP!");
}

//Fonction principale
int cmain()
{
    afficher_message("Hit play to start the simulation...");

    //Choix de la maquette
    selection_maquette(MAQUETTE_B);

    //Initialisation d'un parcours
    QList<int> parcours1,parcours2;
    parcours1 << 24 << 21 << 16 << 17 << 12 << 11 << 6 << 5;
    parcours2 << 19 << 14 << 13 << 10 << 11 << 6 << 3;

    //init + decl troncon critique
    TronconCritique::tronconCritique = new TronconCritique(10,12,3,5);

    //Initialisation des aiguillages de base
    diriger_aiguillage(16,TOUT_DROIT,0);
    diriger_aiguillage(15,DEVIE,0);
    diriger_aiguillage(12,DEVIE,0);
    diriger_aiguillage(11,TOUT_DROIT,0);
    diriger_aiguillage(1,TOUT_DROIT,0);
    diriger_aiguillage(13,DEVIE,0);
    diriger_aiguillage(14,TOUT_DROIT,0);
    diriger_aiguillage(10,TOUT_DROIT,0);
    diriger_aiguillage(9,DEVIE,0);
    diriger_aiguillage(5,TOUT_DROIT,0);
    diriger_aiguillage(3,TOUT_DROIT,0);

    //Initiallisation des aiguillages critiques
    QList<Aiguillage*> aiguillages1,aiguillages2;
    aiguillages1 << new Aiguillage(8,12,TOUT_DROIT,AVANT)
                 << new Aiguillage(7,12,TOUT_DROIT,AVANT)
                 << new Aiguillage(4,6,TOUT_DROIT,AVANT)
                 << new Aiguillage(3,6,TOUT_DROIT,AVANT)
                 << new Aiguillage(8,11,TOUT_DROIT,ARRIERE)
                 << new Aiguillage(7,11,TOUT_DROIT,ARRIERE)
                 << new Aiguillage(4,6,TOUT_DROIT,ARRIERE)
                 << new Aiguillage(3,6,TOUT_DROIT,ARRIERE);

    aiguillages2 << new Aiguillage(8,10,DEVIE,AVANT)
                 << new Aiguillage(7,10,TOUT_DROIT,AVANT)
                 << new Aiguillage(4,6,TOUT_DROIT,AVANT)
                 << new Aiguillage(3,6,DEVIE,AVANT)
                 << new Aiguillage(8,11,DEVIE,ARRIERE)
                 << new Aiguillage(7,11,TOUT_DROIT,ARRIERE)
                 << new Aiguillage(4,3,TOUT_DROIT,ARRIERE)
                 << new Aiguillage(3,3,DEVIE,ARRIERE);

    //Creation des locomotives
    locomotive1 = new Locomotive(1,20,parcours1,1,aiguillages1);
    locomotive2 = new Locomotive(2,20,parcours2,1,aiguillages2);

    locomotive1->fixerPosition(24,5);
    locomotive1->allumerPhares();
    locomotive1->afficherMessage("Ready!");

    locomotive2->fixerPosition(19,3);
    locomotive2->allumerPhares();
    locomotive2->afficherMessage("Ready!");

    locomotive1->start();
    locomotive2->start();

    locomotive1->demarrer();
    locomotive2->demarrer();

    locomotive1->wait();
    locomotive2->wait();

    //Exemple de commande
    afficher_message("Enter a command in the input field at the top of the window.");
    QString commande = getCommand();
    afficher_message(qPrintable(QString("Your command is: ") + commande));

    return EXIT_SUCCESS;
}
