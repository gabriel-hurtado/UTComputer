#include "pile.h"

Pile* Pile::instancePile = nullptr;

Pile& Pile::donnerInstance(){
    if(instancePile==nullptr)
        instancePile= new Pile;
    return *instancePile;
}

void Pile::libererInstance(){
    if(instancePile!=nullptr)
        delete instancePile;
    instancePile = nullptr;
}

/*Cette méthode est réservée à un mementoPile*/

Pile::Pile(const Pile& p){
    /*
        L'objectif est de créer une nouvelle pile
        Il faut donc recopier toutes les valeurs de la pile p.
    */
    for(Litterale* n : p.emP){

        emP.push_front(n);
    }

}

void Pile::voirPile() const {
    for(Litterale* n : emP)
        std::cout<<n->toString()<<std::endl;
}
