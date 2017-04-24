#ifndef THREADLOCO_H
#define THREADLOCO_H

#include <QList>
#include <QThread>
#include "ctrain_handler.h"
#include "locomotive.h"
#include "tronconcritique.h"


class ThreadLoco : public QThread
{
    Locomotive loco;
    QList<int> parcours;
    QList<TronconCritique> troncons;
    int num;
public:
    ThreadLoco(Locomotive loco, int num, QList<int> parcours,
               QList<TronconCritique>troncons);
    void run();
};



#endif // THREADLOCO_H
