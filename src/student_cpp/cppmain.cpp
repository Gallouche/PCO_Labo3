#include "ctrain_handler.h"
#include "locomotive.h"
#include "tronconcritique.h"

#include <QList>

//déclaration des locomotives
Locomotive* locomotive1;
//Locomotive* locomotive2;

//Arret d'urgence
void emergency_stop()
{
    locomotive1->arreter();
    //locomotive2->arreter();
    afficher_message("\nSTOP!");
}

//Fonction principale
int cmain()
{
    afficher_message("Hit play to start the simulation...");

    //Choix de la maquette
    selection_maquette(MAQUETTE_B);

    //Liste des troncons critique
    QList<TronconCritique> troncons;
    //Initialisation des troncons critique
    TronconCritique t1(11,4);
    troncons.push_back(t1);


    //Initialisation d'un parcours
    QList<int> parcours1,parcours2;
    parcours1 << 5 << 24 << 21 << 16 << 17 << 12 << 11 << 6;
    parcours2 << 3 << 19 << 14 << 13 << 10 << 11 << 4;

    //Initialisation des aiguillages
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

    //Creation des locomotives
    locomotive1 = new Locomotive(1,17,parcours1,1);
    //locomotive2 = new Locomotive(2,17,parcours2,1);

    locomotive1->start();
    //locomotive2->start();

    locomotive1->wait();
    //locomotive2->wait();

    //Exemple de commande
    afficher_message("Enter a command in the input field at the top of the window.");
    QString commande = getCommand();
    afficher_message(qPrintable(QString("Your command is: ") + commande));

    return EXIT_SUCCESS;
}
