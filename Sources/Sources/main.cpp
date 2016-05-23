#include "litterales.h"

int main() {


	Rationnel r = Rationnel(13, 5);
	Rationnel r2 = Rationnel(12, 5);
    Litterale* ptr = &r;
    //r = r + r2;
    r.afficher();
    //system("pause");
    if(estdeType<Litterale,Rationnel>(ptr))
        std::cout<<"Patate chaude"<<std::endl;
    else
        std::cout<<"Patate froide"<<std::endl;

    return 0;
}
