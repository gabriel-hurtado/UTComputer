#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include "pile.h"
#include "litteralefactory.h"
#include "operateur.h"
#include "operateurfactory.h"
class Controleur
{
    static Controleur* instanceControleur;
    Controleur();
    virtual ~Controleur();
    Controleur(const Controleur&);
    void operator =(const Controleur&);

public:
    /*Méthodes pour le singleton*/
    static Controleur& donnerInstance();
    static void libererInstance();
    bool commande(QString& s);
    QString firstWord(QString s);


};

#endif // CONTROLEUR_H
