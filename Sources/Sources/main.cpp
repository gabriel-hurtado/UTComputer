#include "litterales.h"
#include "operateur.h"
#include "pile.h"

int main() {


	Rationnel r = Rationnel(13, 5);
	Rationnel r2 = Rationnel(12, 5);

    Entier e= Entier(5);
    Complexe c=Complexe(r,e);
    Entier f(7);
    Litterale* ptr = &r;
    OperateurAddition ad = OperateurAddition(&c,&r2);
    ptr = ad.traitement();
    ptr->afficher();
    //system("pause");

    /*
        Tests pour la pile
    */
    try{
    Pile& p = Pile::donnerInstance();
    p<<r;
    p<<r2;
    p.voirPile();
    std::cout<<"On sauve la pile 1 fois"<<std::endl;
    GerantPile::donnerInstance().sauverPile();
    p<<e;
    p.voirPile();
    std::cout<<"On resauve la pile 2 fois"<<std::endl;
    GerantPile::donnerInstance().sauverPile();
    p<<f;
    p.voirPile();
    std::cout<<"On recharge l'ancienne pile"<<std::endl;
    GerantPile::donnerInstance().UNDO();
    p.voirPile();
    std::cout<<"On recharge l'ancienne pile"<<std::endl;
    GerantPile::donnerInstance().UNDO();
    p.voirPile();
    std::cout<<"On recharge la pile stockée 2"<<std::endl;
    GerantPile::donnerInstance().REDO();
    p.voirPile();
    std::cout<<"On recharge la pile stockée 1"<<std::endl;
    GerantPile::donnerInstance().REDO();
    p.voirPile();
    }
    catch(LitteraleException& e){
        std::cout<<e.getMessage();
    }
    return 0;
}
