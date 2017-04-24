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
