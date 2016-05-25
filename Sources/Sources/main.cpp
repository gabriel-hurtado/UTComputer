#include "litterales.h"
#include "operateur.h"
#include "pile.h"

int main() {


	Rationnel r = Rationnel(13, 5);
	Rationnel r2 = Rationnel(12, 5);
    Entier e= Entier(5);
    Litterale* ptr = &r;
    OperateurAddition ad = OperateurAddition(&r,&e);
    ptr = ad.traitement();
    ptr->afficher();
    //system("pause");
    if(estdeType<Rationnel>(ptr))
        std::cout<<"Patate chaude"<<std::endl;
    else
        std::cout<<"Patate froide"<<std::endl;

    /*
        Tests pour la pile
    */
    Pile& p = Pile::donnerInstance();
    p<<r;
    p<<r2;
    p.voirPile();
    std::cout<<"On sauve la pile"<<std::endl;
    GerantPile::donnerInstance().sauverPile();
    p<<e;
    p.voirPile();
    std::cout<<"On recharge l'ancienne pile"<<std::endl;
    GerantPile::donnerInstance().UNDO();
    p.voirPile();
    return 0;
}
