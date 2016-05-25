#include "litterales.h"
#include <deque>
#ifndef PILE_H
#define PILE_H

class MementoPile;
/*
    Manuel pour utiliser un objet "deque" :
    http://en.cppreference.com/w/cpp/container/deque
*/
/*
    Pile est l'Originator du Memento
*/
class Pile
{
    std::deque<Litterale*> emP;//emP stands for "embedded Pile"
    static Pile* instancePile;

    /*made those method in private so the user can't use them*/
    Pile(){}
    Pile(const Pile& p);
    ~Pile(){}
    void operator=(const Pile&);

public:
    friend class MementoPile; //Help for the constructor of a MementoPile
    Pile& operator<<(Litterale& l){emP.push_front(&l);return *this;}
    Pile& operator>>(Litterale* l){*l=*emP.front();return *this;}
    void voirPile() const;
    static Pile& donnerInstance();
    static void libererInstance();
    //Méthodes pour le Memento
    MementoPile* saveInMemento() const;
    void restoreFromMemento(MementoPile* m);
    /*AJOUTER UN ITERATOR SUR LA PILE*/

};


/*
    Classe MementoPile :
        crée des objets qui contiennent une sauvegarde de la pile
*/
class MementoPile{
    std::deque<Litterale*> saved_emP;
public:
    friend class Pile; //Pour que la Pile puisse acceder au saved_emP d'un MementoPile (on casse ici l'encapsulation mais ces classes ne sont normalement pas utilisées par l'User)
    friend class GerantPile;//Pour que le GerantPile puisse acceder au saved_emP d'un Memento (on casse ici l'encapsulation mais ces classes ne sont normalement pas utilisées par l'User)
    MementoPile(const std::deque<Litterale* >& emP);
};

class GerantPile{
    unsigned int nombreMaxDeMemento;
    unsigned int nombreDeMemento;
    MementoPile** savedMemento;
    static GerantPile *instanceGerantPile;

    GerantPile(unsigned int nbMax = 1);
    ~GerantPile();
    GerantPile(const GerantPile&);
    void operator=(const GerantPile& g);

public:
    friend class MementoPile;
    static GerantPile& donnerInstance();
    static void libererInstance();
    GerantPile& push_front(MementoPile* l);
    MementoPile* pop_front();
    void sauverPile();
    void UNDO();
    void REDO();


};
#endif // PILE_H
