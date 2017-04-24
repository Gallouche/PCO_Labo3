#ifndef AIGUILLAGE_H
#define AIGUILLAGE_H


class Aiguillage
{
    int num;
    int contactDecl;
    int direction;
    int sens;

public:
    Aiguillage(int num, int contactDecl, int direction, int sens);
    int getNum();
    int getContactDecl();
    int getSens();
    int getDirection();
};

#endif // AIGUILLAGE_H
