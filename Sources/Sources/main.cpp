#include "litterales.h"
#include "operateur.h"
#include "pile.h"

int main() {


    Reelle r = Reelle(1, 0);
    r.afficher();
    std::cout<<"\n";

    Entier e= Entier(5);
    LitteraleNumerique* l= &(r.Simplification());
    OperateurAddition ad= OperateurAddition(&r,&e);
    Litterale* l2= ad.traitementOperateur();
    //system("pause");

    /*
        Tests pour la pile

    try{
    Pile& p = Pile::donnerInstance();
    std::cout<<"On ajoute un élément à la pile"<<std::endl;
    p<<r;
    std::cout<<"On ajoute un élément à la pile"<<std::endl;
    p<<r;
    p.voirPile();
    std::cout<<"On ajoute un élément à la pile"<<std::endl;
    p<<e;
    p.voirPile();
    std::cout<<"On ajoute un élément à la pile"<<std::endl;
    p<<f;
    p.voirPile();
    std::cout<<"On recharge l'ancienne pile"<<std::endl;
    p.UNDO();
    p.voirPile();
    std::cout<<"On recharge l'ancienne pile"<<std::endl;
    p.UNDO();
    p.voirPile();
    std::cout<<"On recharge la pile stockée 2"<<std::endl;
    p.REDO();
    p.voirPile();
    std::cout<<"On recharge la pile stockée 1 on revient donc à l'état courant de la pile"<<std::endl;
    p.REDO();
    p.voirPile();
    std::cout<<"On ajoute un élément à la pile"<<std::endl;
    p<<r;
    p.voirPile();
    /*std::cout<<"On essaye de REDO après insertion, mais cela est interdit car cela n'a pas de sens"<<std::endl;
    p.REDO();
        //pour récuperer un élément de la pile
    Litterale* k;

    p>>k;
    p.UNDO();
    p>>k;
    std::cout<<k->toString();
    }



    catch(LitteraleException& e){
        std::cout<<e.getMessage();
    }
    */
    return 0;
}
