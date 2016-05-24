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
