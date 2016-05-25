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
GerantPile* GerantPile::instanceGerantPile=nullptr;

GerantPile::GerantPile(unsigned int nbMax):nombreMaxDeMemento(nbMax),nombreDeMemento(0),savedMemento(new MementoPile*[nbMax]){}

/*
 Le destructeur du GerantPile doit détruire toutes les Litterale* sauvés dans des Memento puis le tableau des Memento
 En effet le Memento ne doit pas supprimer tout seul les litterales car une version du memento sera chargée dans la Pile
*/
GerantPile::~GerantPile(){
    for(unsigned int i=0;i<nombreDeMemento;i++){
        for(Litterale* n : savedMemento[i]->saved_emP){
            delete n;
        }

    }

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

GerantPile& GerantPile::push_front(MementoPile* l){
    if(nombreDeMemento==nombreMaxDeMemento){
        //On doit reconstruire un savedMemento plus grand
        MementoPile** newsavedMemento = new MementoPile*[nombreMaxDeMemento*2];
        for(unsigned int i = 0; i < nombreMaxDeMemento*2;i++)
            newsavedMemento[i]=savedMemento[i]; //Trasnfert des pointeurs
        delete savedMemento;
        savedMemento= newsavedMemento;
        nombreMaxDeMemento*=2;
    }
    savedMemento[nombreDeMemento++]=l;
    return *this;
}

MementoPile* GerantPile::pop_front(){
    if(nombreDeMemento==0)
        throw LitteraleException("Impossible de UNDO : Pas de sauvegarde de la pile !");
    return savedMemento[nombreDeMemento--];
}

void GerantPile::UNDO(){
    //On chope l'instance de la pile dans un Memento
    MementoPile* TempMemento = Pile::donnerInstance().saveInMemento();
    //On dépile la derniere instace du Gerant que l'on envoie dans la pile
    Pile::donnerInstance().restoreFromMemento(this->pop_front());
    //On sauvegarde l'état de Pile
    push_front(TempMemento);

}
void GerantPile::REDO(){
    //Destruction des Litterale* ici
}

