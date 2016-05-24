#include "litterales.h"
#include <deque>
#ifndef PILE_H
#define PILE_H

/*
    Manuel pour utiliser un objet deque :
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


    static Pile& donnerInstance();
    static void libererInstance();

};

#endif // PILE_H
