#include "rationnel.h"
#include <iostream>

int main() {


	Rationnel r = Rationnel(13, 5);
	Rationnel r2 = Rationnel(12, 5);
	r = r + r2;
	std::cout<<r.afficher();
    //system("pause");
    return 0;
}
