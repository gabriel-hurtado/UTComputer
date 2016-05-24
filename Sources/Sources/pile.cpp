#include "pile.h"





/*---------Méthodes de Pile-----------*/
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

void Pile::voirPile() const {
    for(Litterale* n : emP)
        std::cout<<n->toString()<<std::endl;
}

MementoPile* Pile::saveInMemento() const{
    return new MementoPile(emP);
}

void Pile::restoreFromMemento(MementoPile* m){
    emP= m->saved_emP;
}

/*---------Méthodes de MementoPile-----------*/

MementoPile::MementoPile(const std::deque<Litterale* >& emP){
    //On push par le back from the front
    for(Litterale* n : emP)
        saved_emP.push_back(n->getCopy());

}

/*---------Méthodes de GerantPile-----------*/
GerantPile::GerantPile(unsigned int nbMax =1):nombreMaxDeMemento(nbMax),nombreDeMemento(0),savedMemento(new MementoPile[1]){}
/*
 Le destructeur du GerantPile doit détruire toutes les Litterale* sauvés dans des Memento puis le tableau des Memento
 En effet le Memento ne doit pas supprimer tout seul
*/
GerantPile::~GerantPile(){
    for(unsigned int i=0;i<nombreDeMemento;i++){
        for(Litterale* n : savedMemento[i].saved_emP){
            delete n;
        }
    }
    delete savedMemento[i];
}

GerantPile& GerantPile::donnerInstance(){
    if(instanceGerantPile==nullptr)
        instanceGerantPile= new GerantPile;
    return *instanceGerantPile;
}

void GerantPile::libererInstance(){
    if(instanceGerantPile!=nullptr)
        delete instanceGerantPile;
    instanceGerantPile = nullptr;
}

void GerantPile::UNDO(){
    if()
}

void GerantPile::REDO(){
    //Destruction des Litterale* ici
}

