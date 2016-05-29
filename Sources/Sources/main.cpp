#include "litterales.h"
#include "operateur.h"
#include "pile.h"
#include "litteralefactory.h"

int main() {

    LitteraleFactory& lf = LitteraleFactory::donnerInstance();
    LitteraleFactory::enregistrer("Réelle",new Reelle(0,0));
    LitteraleFactory::enregistrer("Entier",new Entier(0));

    Reelle r = Reelle(1, 0);
    std::cout<<"\n";

    Entier e= Entier(5);
    Complexe c1 = Complexe(r,e);
    Complexe c2= Complexe(e,r);
    OperateurDivision ad= OperateurDivision(&c1,&c2);
    Litterale* l2= ad.traitementOperateur();
    l2->afficher();
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
