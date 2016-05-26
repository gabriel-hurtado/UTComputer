#include "litterales.h"
#include "operateur.h"
#include "pile.h"

int main() {


	Rationnel r = Rationnel(13, 5);
    Rationnel* r2 ;

    Entier e= Entier(5);
    Complexe c=Complexe(r,e);
    Entier f(7);
    Litterale* ptr = &r;
    //system("pause");

    /*
        Tests pour la pile
    */
    try{
    Pile& p = Pile::donnerInstance();
    std::cout<<"On ajoute un élément à la pile"<<std::endl;
    p<<r;
    //comment marche la lecture depuis la pile ? (seg fault dans les lignes suivantes commentées !
    //p>>r2;
   // r2->afficher();
    }
    catch(LitteraleException& e){
        std::cout<<e.getMessage();
    }
    return 0;
}
