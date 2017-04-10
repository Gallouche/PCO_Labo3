#include "threadloco.h"

ThreadLoco::ThreadLoco(Locomotive loco, int num,QList<int> parcours, int debutCrit, int finCrit):
    loco(loco),
    num(num),
    parcours(parcours),
    debutCrit(debutCrit),
    finCrit(finCrit)
{}

void ThreadLoco::run(){
    loco.fixerNumero(num);
    loco.fixerVitesse(20);
    loco.fixerPosition(parcours.at(0),parcours.at(parcours.size()-1));
    loco.allumerPhares();
    loco.afficherMessage("Ready!");

    for(int i = 1; i < parcours.size(); i++){
        attendre_contact(parcours.at(i));
        loco.afficherMessage(QString("I've reached contact no. %1.").arg(parcours.at(i)));
    }

    loco.arreter();
    loco.afficherMessage("I'm done!");
}
