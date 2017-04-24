/**
 * File:       tronconcritique.h
 *
 * Created by: Kevin M. Theo G.
 * Created on: 25.03.2017
 */

#ifndef TRONCONCRITIQUE_H
#define TRONCONCRITIQUE_H

#include <QSemaphore>
#include <QList>

#include "locomotive.h"

class TronconCritique {

    //Les contacts aux extremités du tronçon Critique
    int cont1, cont2, cont3, cont4;

    bool troncLibre  = true;     //tronçon libre ou non
    bool attenteLoco = false;    //locomotives en attente ou non

    QSemaphore* mutVar;         // mutex pour troncLibre et pour attente, deux booleen qui indique l'état du tronçon
    QSemaphore* mutListeAttente; // mutex pour listeAttente, la liste des attentes de tronçon critique

    QSemaphore* semAttenteLoco;  // sémaphore attente des locomotives, pour entrer dans le tronçon critique

    QList<Locomotive*> listeAttente = QList<Locomotive*>(); // Liste attente du tronçon critique

public:
    static TronconCritique *tronconCritique;

    /**
     * Constructeur d'un tronçon critique.
     * @param c1 1er contact du tronçon critique
     * @param c2 2eme contact du tronçon critique
     * @param c3 3eme contact du tronçon critique
     * @param c4 4eme contact du tronçon critque
     */
    TronconCritique(int c1, int c2, int c3, int c4);

    /**
     * @return tronçon libre ou non
     */
    bool tronconLibre();

    /**
     * @param c Le contact à verifier
     * @return si le contact c, est un bord du tronçon critique
     */
    bool bordTroncon(int c);

    /**
     * inscrit l dans la liste des demandeur du tronçon, (prise en compte de la priorité de l)
     * @param l La locomotive qui demande l'utilisation d'un troncon
     */
    void demandeTroncon(Locomotive* l);

    /**
     * libere le troncon detenu par l (locomotive)
     * @param l La locomotive qui libère le tronçon
     */
    void libererTroncon(Locomotive* l);

    /**
     * bloc le tronçon pour l
     * @param l La locomotive qui bloc le tronçon pour sa propre utilisation
     */
    void bloqueTroncon(Locomotive* l);

};

#endif // TRONCONCRITIQUE_H
