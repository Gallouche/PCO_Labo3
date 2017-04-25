/**
 * -------------------------------------------------------------------------------
 * Laboratoire : PCO - Labo3
 * Fichier     : aiguillage.h
 * Auteur(s)   : Théo Gallandat & Kevin Moreira
 * Date        : 24/04/2017
 *
 * But         : Fourni une classe aiguillage pour la gestion dynamique des
 *               aiguillages.
 *
 * Remarque(s) : R.A.S.
 -------------------------------------------------------------------------------
 */

#ifndef AIGUILLAGE_H
#define AIGUILLAGE_H

/**
 * @brief The Aiguillage class représente un aiguillage
 */
class Aiguillage
{
    int num;
    int contactDecl;
    int direction;
    int sens;

public:
    /**
     * @brief Aiguillage Constructeur
     * @param num Numéro de l'aiguillage
     * @param contactDecl Contact ou l'on doit changer l'aiguillage
     * @param direction direction de l'aiguillage
     * @param sens sens de l'aiguillage
     */
    Aiguillage(int num, int contactDecl, int direction, int sens);
    int getNum();
    int getContactDecl();
    int getSens();
    int getDirection();
};

#endif // AIGUILLAGE_H
