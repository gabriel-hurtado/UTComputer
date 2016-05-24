#include "litterales.h"
#include <deque>
#ifndef PILE_H
#define PILE_H

/*
    Manuel pour utiliser un objet "deque" :
    http://en.cppreference.com/w/cpp/container/deque
*/
class Pile
{
    std::deque<Litterale*> emP;
    static Pile* instancePile;
    Pile(){}
    Pile(const Pile& p);
    ~Pile(){}
    void operator=(const Pile&);
public:
    Pile& operator<<(Litterale& l){emP.push_front(&l);return *this;}
    Pile& operator>>(Litterale* l){*l=*emP.front();return *this;}
    void voirPile() const;
    static Pile& donnerInstance();
    static void libererInstance();

};

class MementoPile{

public:
    friend class Pile;
};

#endif // PILE_H
