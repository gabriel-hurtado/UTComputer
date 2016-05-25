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

Pile& Pile::operator<<(Litterale& l){
    GerantPile::donnerInstance().clearREDO();
    emP.push_front(&l);return *this;
}

Pile& Pile::operator>>(Litterale* l){
    *l=*emP.front();return *this;
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

GerantPile::GerantPile(unsigned int nbMaxUNDO,unsigned int nbMaxREDO):
    nombreMaxDeMementoUNDO(nbMaxUNDO),nombreDeMementoUNDO(0),savedMementoUNDO(new MementoPile*[nbMaxUNDO]),
    nombreMaxDeMementoREDO(nbMaxREDO),nombreDeMementoREDO(0),savedMementoREDO(new MementoPile*[nbMaxREDO]){}

/*
 Le destructeur du GerantPile doit détruire toutes les Litterale* sauvés dans des Memento puis le tableau des Memento
 En effet le Memento ne doit pas supprimer tout seul les litterales car une version du memento sera chargée dans la Pile
*/
GerantPile::~GerantPile(){
    for(unsigned int i=0;i<nombreDeMementoUNDO;i++){
        for(Litterale* n : savedMementoUNDO[i]->saved_emP){
            delete n;
        }

    }
    for(unsigned int i=0;i<nombreDeMementoREDO;i++){
        for(Litterale* n : savedMementoREDO[i]->saved_emP){
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

GerantPile& GerantPile::push_front_undo(MementoPile* l){
    if(nombreDeMementoUNDO==nombreMaxDeMementoUNDO){
        //On doit reconstruire un savedMemento plus grand
        MementoPile** newsavedMemento = new MementoPile*[nombreMaxDeMementoUNDO*2];
        for(unsigned int i = 0; i < nombreMaxDeMementoUNDO*2;i++)
            newsavedMemento[i]=savedMementoUNDO[i]; //Trasnfert des pointeurs
        delete savedMementoUNDO;
        savedMementoUNDO= newsavedMemento;
        nombreMaxDeMementoUNDO*=2;
    }
    savedMementoUNDO[nombreDeMementoUNDO++]=l;
    return *this;
}

MementoPile* GerantPile::pop_front_undo(){
    if(nombreDeMementoUNDO==0)
        throw LitteraleException("Impossible de UNDO : Pas de sauvegarde de la pile !");
    return savedMementoUNDO[--nombreDeMementoUNDO];
}

GerantPile& GerantPile::push_front_redo(MementoPile* l){
    if(nombreDeMementoREDO==nombreMaxDeMementoREDO){
        //On doit reconstruire un savedMemento plus grand
        MementoPile** newsavedMemento = new MementoPile*[nombreMaxDeMementoREDO*2];
        for(unsigned int i = 0; i < nombreMaxDeMementoREDO*2;i++)
            newsavedMemento[i]=savedMementoREDO[i]; //Trasnfert des pointeurs
        delete savedMementoREDO;
        savedMementoREDO= newsavedMemento;
        nombreMaxDeMementoREDO*=2;
    }
    savedMementoREDO[nombreDeMementoREDO++]=l;
    return *this;
}

MementoPile* GerantPile::pop_front_redo(){
    if(nombreDeMementoREDO==0)
        throw LitteraleException("Impossible de REDO : Pas de sauvegarde de la pile !");
    return savedMementoREDO[--nombreDeMementoREDO];
}

void GerantPile::UNDO(){
    //On chope l'instance de la pile dans un Memento
    MementoPile* TempMemento = Pile::donnerInstance().saveInMemento();
    //On dépile la derniere instace du Gerant que l'on envoie dans la pile
    MementoPile* m = this->pop_front_undo();
    Pile::donnerInstance().restoreFromMemento(m);
    //On sauvegarde l'état de Pile
    push_front_redo(TempMemento);

}
void GerantPile::REDO(){
    //On chope l'instance de la pile dans un Memento
    MementoPile* TempMemento = Pile::donnerInstance().saveInMemento();
    //On dépile la derniere instace du Gerant que l'on envoie dans la pile
    MementoPile* m = this->pop_front_redo();
    Pile::donnerInstance().restoreFromMemento(m);
    //On sauvegarde l'état de Pile
    push_front_undo(TempMemento);
}

void GerantPile::sauverPile(){
    push_front_undo(Pile::donnerInstance().saveInMemento());
}

void GerantPile::clearREDO(){
    //On nettoie les REDO en attente car useless
    for(unsigned int i=0;i<nombreDeMementoREDO;i++){
        for(Litterale* n : savedMementoREDO[i]->saved_emP){
            delete n;
        }
    }
    nombreDeMementoREDO=0;

}
