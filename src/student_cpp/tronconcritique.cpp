#include "tronconcritique.h"

TronconCritique::TronconCritique(int debut, int fin):
    contactDebut(debut),
    contactFin(fin),
    libre(true)
{
    mutex = new QSemaphore(1);
    waiting = new QSemaphore(0);
}
TronconCritique::~TronconCritique(){
    delete mutex;
    delete waiting;
}

int TronconCritique::getDebut(){
    return contactDebut;
}

int TronconCritique::getFin(){
    return contactFin;
}

bool TronconCritique::estLibre(){
    return libre;
}

void TronconCritique::acces(){
    mutex->acquire();
    if(libre){
        libre = false;
        mutex->release();
        return;
    }
    else{
        waiting->acquire();
        return;
    }
}

void TronconCritique::liberer(){
    mutex->acquire();
    libre = true;
    waiting->release();
    mutex->release();
}
