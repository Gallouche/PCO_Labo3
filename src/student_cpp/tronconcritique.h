#ifndef TRONCONCRITIQUE_H
#define TRONCONCRITIQUE_H

#include <QSemaphore>

class TronconCritique
{
    int contactDebut;
    int contactFin;
    bool libre;

    QSemaphore* mutex;
    QSemaphore* waiting;

public:
    TronconCritique(int debut, int fin);
    ~TronconCritique();
    int getDebut();
    int getFin();
    bool estLibre();
    void acces();
    void liberer();
};

#endif // TRONCONCRITIQUE_H
