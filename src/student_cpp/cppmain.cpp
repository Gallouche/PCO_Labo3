/**
 * -------------------------------------------------------------------------------
 * Laboratoire : PCO - Labo3
 * Fichier     : cppmain.cpp
 * Auteur(s)   : Théo Gallandat & Kevin Moreira
 * Date        : 24/04/2017
 *
 * But         : Fourni une amorce pour la simulation et défini les paramètres
 *               utiles.
 *
 * Remarque(s) : Nous avons choisi de modifier la classe locomitive de façon
 *      a la rendre héritière de Qthread, et de gerer directement
 *      la concurence a l'interieur de la classe et non pas en passant
 *      un locomitive a une une autre classe thread.
 *      Nous avons modifier le constructeur de façon a pouvoir lui passer
 *      les paramètre voulu tel que le parcours a effectuer, les
 *      aiguillages dynamique et sa priorité.
 *
 *      Nous avons crée un classe aiguillage pour gere les changement
 *      a effectuer en entrée et sortie de troncon critique, car les
 *      locomotives ne suivent logiquement pas le même parcours et
 *      les orientations ne peuvent pas etre définie statiquement.
 *
 *      Nous avons crée un classe TronconCritique qui permet de definir
 *      des troncons critique, et d'y gere les acces des différentes
 *      locomotives.
 -------------------------------------------------------------------------------
 */
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
    parcours1 << 16 << 17 << 12 << 11 << 6 << 5 << 24 << 21;
    parcours2 << 13 << 10 << 11 << 6 << 3 << 19 << 14 ;

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

    //Initiallisation des aiguillages critiques dynamique
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
    locomotive1 = new Locomotive(1,12,parcours1,2,aiguillages1);
    locomotive2 = new Locomotive(2,12,parcours2,1,aiguillages2);

    locomotive1->fixerPosition(16,21);
    locomotive1->allumerPhares();
    locomotive1->afficherMessage("Ready!");

    locomotive2->fixerPosition(13,14);
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
