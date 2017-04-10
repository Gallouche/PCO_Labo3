#ifndef THREADLOCO_H
#define THREADLOCO_H

#include <QList>
#include <QThread>
#include "ctrain_handler.h"
#include "locomotive.h"


class ThreadLoco : public QThread
{
    Locomotive loco;
    QList<int> parcours;
    int debutCrit;
    int finCrit;
    int num;
public:
    ThreadLoco(Locomotive loco, int num, QList<int> parcours, int debutCrit, int finCrit);
    void run();
};



#endif // THREADLOCO_H
