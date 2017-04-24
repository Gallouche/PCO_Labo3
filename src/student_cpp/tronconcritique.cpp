/**
 * File:       tronconcritique.cpp
 *
 * Created by: Kevin M. Theo G.
 * Created on: 25.03.2017
 */

#include "ctrain_handler.h"
#include "tronconcritique.h"

TronconCritique *TronconCritique::tronconCritique = nullptr;

TronconCritique::TronconCritique(int c1, int c2, int c3, int c4)
    : cont1(c1), cont2(c2), cont3(c3), cont4(c4)
{
    //initialisation des deux mutex
    mutVar          = new QSemaphore(1);
    mutListeAttente = new QSemaphore(1);

    //initialisation du semaphore
    semAttenteLoco  = new QSemaphore(0);
}

bool TronconCritique::tronconLibre()
{
    mutVar->acquire();
    bool troncLibreTemp = troncLibre; //var temporaire, pour pouvoir release avant le return
    mutVar->release();

    return troncLibreTemp;
}

bool TronconCritique::bordTroncon(int c)
{
    return c == cont1 || c == cont2 || c == cont3 || c == cont4; //si c fait partie d'un des 4 c1...c4 c'est bon
}

void TronconCritique::libererTroncon(Locomotive* l)
{
    mutVar->acquire();
    troncLibre = true;

    if(attenteLoco) //release que si locomotive est en attente (evite release inutiles)
    {
        semAttenteLoco->release();
    }
    mutVar->release();

    listeAttente.removeAll(l);
}


void TronconCritique::demandeTroncon(Locomotive* l)
{
    mutListeAttente->acquire();
    listeAttente << l;
    mutListeAttente->release();
}

void TronconCritique::bloqueTroncon(Locomotive* l)
{
    Locomotive *locoPriorSup = l; //la locomotive avec la priorité superieure

    mutListeAttente->acquire();

    for(int i = 0; i < listeAttente.size(); i++)
    {
        Locomotive* currentL = listeAttente.at(i);
        if(currentL->getPriorite() < l->getPriorite())
        {
            locoPriorSup = currentL;
        }
    }

    mutListeAttente->release();

    mutVar->acquire();

    bool troncLibreTemp = troncLibre; //var temporaire, pour pouvoir release avant le return

    if(!troncLibreTemp || locoPriorSup != l)
    {
        l->arreter();
        attenteLoco = true;

        mutVar->release();
        semAttenteLoco->acquire();
        mutVar->acquire();

        attenteLoco = false;

        l->demarrer();
    }

    troncLibre = false;

    mutVar->release();
}
