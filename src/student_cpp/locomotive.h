#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include <QString>
#include <QThread>
#include <QList>
#include "aiguillage.h"

#define AVANT 1
#define ARRIERE 0

class Locomotive : public QThread
{
    int _numero;
    int _vitesse;
    bool _enFonction;
    int _priorite;
    QList<int> _parcours;
    QList<Aiguillage*> _aiguillages;
    int _sens;

public:

    /** Constructeur.
     * Initialise la locomotive avec un numero invalide et une vitesse nulle.
     */
    Locomotive();

    /** Constructeur.
     * Initialise la locomotive en precisant son numero et sa vitesse initiale.
     * @param numero Numero de la locomotive.
     * @param vitesse Vitesse initiale de la locomotive.
     */
    Locomotive(int numero, int vitesse, QList<int> parcours,
               int priorite, QList<Aiguillage*> aiguillages);

    ~Locomotive();

    /**
     * @brief run
     */
    void run();

    /** Retourne le numero de la locomotive.
     * @return Numero de la locomotive.
     */
    int numero() const;

    /** Fixe le numero de la locomotive.
     * @param numero Numero de la locomotive.
     */
    void fixerNumero(int numero);

    /** Retourne la vitesse actuelle de la locomotive.
     * @return Vitesse actuelle de la locomotive.
     */
    int vitesse() const;

    /** Fixe la vitesse de la locomotive.
     * Si la locomotive est en fonction, alors sa vitesse est modifiee en
     * consequence.
     * @param vitesse Vitesse de la locomotive.
     */
    void fixerVitesse(int vitesse);

    /** Determine la position initiale de la locomotive.
     * @param contactAvant Contact vers lequel la locomotive va se diriger.
     * @param contactArrier Contact a l'arriere de la locomotive.
     */
    void fixerPosition(int contactAvant, int contactArriere);

    /** Affiche un message.
     * @param message Message a afficher.
     */
    void afficherMessage(const QString &message);

    //! Allume les phares de la locomotive.
    void allumerPhares();

    //! Eteint les phares de la locomotive.
    void eteindrePhares();

    //! Demarre la locomotive.
    void demarrer();

    //! Arrete la locomotive.
    void arreter();

    //! Change le sens de marche de la locomotive.
    void inverserSens();

    //changer la priorite de la locomotive
    void fixerPriorite(int priorite);

    //getter sur la priorite
    int getPriorite();
};

#endif // LOCOMOTIVE_H
