#include "rationnel.h"

int main() {


	Rationnel r = Rationnel(13, 5);
	Rationnel r2 = Rationnel(12, 5);
	r = r + r2;
    r.afficher();
    //system("pause");
    return 0;
}
