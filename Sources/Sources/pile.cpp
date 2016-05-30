#include "pile.h"

/*---------Méthodes de Pile-----------*/
Pile* Pile::instancePile = nullptr;
/*
   Donne l'instance courante de la pile
*/
Pile& Pile::donnerInstance(){
    if(instancePile==nullptr)
        instancePile= new Pile;
    return *instancePile;
}
/*
    Détruit l'instance courante de la Pile
    TODO : supprimer les éléments de la pile quand on la détruit
*/
void Pile::libererInstance(){
    if(instancePile!=nullptr)
        delete instancePile;
    instancePile = nullptr;
}
/*
    operator<< :
    Rajoute un élément à la pile.
    La méthode fait bien attention à nettoyer les possibles REDO, car ils doivent disparaitre lors de l'insertion d'un nouvel élément : ils n'ont plus aucun sens
    La méthode effectue aussi avant de rajouter l'élément, une sauvergarde de la pile pour un possible UNDO
*/
Pile& Pile::operator<<(Litterale& l){
    GerantPile::donnerInstance().clearREDO();
    sauverPile();
    emP.push_back(&l);return *this;
}

Pile& Pile::operator>>(Litterale*& l){
   if(!emP.empty()){ l=emP.back();emP.pop_back();return *this;}
    else throw PileException("Pile vide, impossible de dépiler");
}

void Pile::voirPile() const {
    for(Litterale* n : emP)
        std::cout<<n->toString().toStdString()<<std::endl;
}

MementoPile* Pile::saveInMemento() const{
    return new MementoPile(emP);
}

void Pile::restoreFromMemento(MementoPile* m){
    emP= m->saved_emP;
}

void Pile::UNDO(){
    GerantPile::donnerInstance().UNDO();
}
void Pile::REDO(){
    GerantPile::donnerInstance().REDO();
}
void Pile::sauverPile(){
    GerantPile::donnerInstance().sauverPile();
}

/*---------Méthodes de MementoPile-----------*/
 /*
    On construit un MementoPile en lui donnant un état de la pile
*/
MementoPile::MementoPile(const std::vector<Litterale* >& emP){
    //On push par le back from the back
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
 /*
    donnerInstance :
    donne l'instance du Gerant de la pile.
 */
GerantPile& GerantPile::donnerInstance(){
    if(instanceGerantPile==nullptr)
        instanceGerantPile= new GerantPile;
    return *instanceGerantPile;
}
 /*
    libereInstance :
    On détruit l'instance courante du Gerant de la pile
    Il faut donc détruire toutes les littérales stockées dans les vecteurs des possibles UNDO et REDO
 */
void GerantPile::libererInstance(){
    if(instanceGerantPile!=nullptr)
        delete instanceGerantPile;
    instanceGerantPile = nullptr;
}
/*
   push_back_undo :
   On push un état de la pile correspondant à un possible UNDO
*/
GerantPile& GerantPile::push_back_undo(MementoPile* l){
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
 /*
    pop_back_undo :
    On renvoie l'état de la pile précédent en cas de UNDO
 */
MementoPile* GerantPile::pop_back_undo(){
    if(nombreDeMementoUNDO==0)
        throw LitteraleException("Impossible de UNDO : Pas de sauvegarde de la pile !");
    return savedMementoUNDO[--nombreDeMementoUNDO];
}
 /*
    push_back_redo :
    On push un état de la pile correspondant à un possible REDO
*/
GerantPile& GerantPile::push_back_redo(MementoPile* l){
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
 /*
   pop_back_redo :
   On renvoie l'état de la pile précédent en cas de REDO
*/
MementoPile* GerantPile::pop_back_redo(){
    if(nombreDeMementoREDO==0)
        throw LitteraleException("Impossible de REDO : Pas de sauvegarde de la pile !");
    return savedMementoREDO[--nombreDeMementoREDO];
}
 /*
    UNDO :
    Recharge l'état de la pile avant la dernière insertion
*/
void GerantPile::UNDO(){
    //On chope l'instance de la pile dans un Memento
    MementoPile* TempMemento = Pile::donnerInstance().saveInMemento();
    //On dépile la derniere instace du Gerant que l'on envoie dans la pile
    MementoPile* m = this->pop_back_undo();
    Pile::donnerInstance().restoreFromMemento(m);
    //On sauvegarde l'état de Pile
    push_back_redo(TempMemento);

}
/*
    REDO :
    Recharge l'état qui précède le UNDO
*/
void GerantPile::REDO(){
    //On chope l'instance de la pile dans un Memento
    MementoPile* TempMemento = Pile::donnerInstance().saveInMemento();
    //On dépile la derniere instace du Gerant que l'on envoie dans la pile
    MementoPile* m = this->pop_back_redo();
    Pile::donnerInstance().restoreFromMemento(m);
    //On sauvegarde l'état de Pile
    push_back_undo(TempMemento);
}
/*
    sauverPile :
    Permet sauvegarder la pile dans le vecteur des UNDO possibles
    Utile à chaque fois que l'on insere un élément dans la pile
*/
void GerantPile::sauverPile(){
    push_back_undo(Pile::donnerInstance().saveInMemento());
}

/*
    clearREDO :
    Nettoie les Littérales stockés dans les vecteurs contennant les REDO possibles
    Est utilisé par Pile::operator << car lors d'une insertion les REDO sont effacés
*/
void GerantPile::clearREDO(){
    //On nettoie les REDO en attente car useless
    for(unsigned int i=0;i<nombreDeMementoREDO;i++){
        for(Litterale* n : savedMementoREDO[i]->saved_emP){
            delete n;
        }
    }
    nombreDeMementoREDO=0;

}
