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


#include "aiguillage.h"

Aiguillage::Aiguillage(int num, int contactDecl, int direction,
                       int sens):
    num(num),
    contactDecl(contactDecl),
    direction(direction),
    sens(sens)
{}

int Aiguillage::getNum(){
    return num;
}

int Aiguillage::getContactDecl(){
    return contactDecl;
}

int Aiguillage::getSens(){
    return sens;
}

int Aiguillage::getDirection(){
    return direction;
}
