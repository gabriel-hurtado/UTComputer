#include "litterales.h"

class Entier : public LitteraleNumerique {

	int valeur;
public:
    Entier(int v=0) :valeur(v) {}
    ~Entier() {};
    int getValeur() const { return valeur; }
    const std::string toString() const { return std::to_string(getValeur()); }


    /*Les opérateurs sont dorénavant des objets*/
    /*
	Entier operator+(Entier e) { return Entier(e.getValeur() + getValeur()); }
	Entier operator+(int e) { return Entier(e+ getValeur()); }
	Entier operator*(Entier e) { return Entier(e.getValeur() * getValeur()); }
	Entier operator*(int e) { return Entier(e * getValeur()); }
    */
};
