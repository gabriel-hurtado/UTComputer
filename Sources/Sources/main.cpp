#include "litterales.h"
#include "operateur.h"

int main() {


	Rationnel r = Rationnel(13, 5);
	Rationnel r2 = Rationnel(12, 5);
    Litterale* ptr = &r;
    OperateurAddition ad = OperateurAddition(&r,&r2);
    ptr = estdeType<Rationnel>(ad.traitement());
    ptr->afficher();
    //system("pause");
    if(estdeType<Rationnel>(ptr))
        std::cout<<"Patate chaude"<<std::endl;
    else
        std::cout<<"Patate froide"<<std::endl;

    return 0;
}
