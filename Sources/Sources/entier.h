#include "litterales.h"
class Entier : public LitteraleNumerique {
	int valeur;
public:
	Entier(int v=0) :valeur(v) {}
	int getValeur() const { return valeur; }
	const std::string afficher() { return std::to_string(getValeur()); }
	~Entier() { LitteraleNumerique::~LitteraleNumerique(); }
	Entier operator+(Entier e) { return Entier(e.getValeur() + getValeur()); }
	Entier operator+(int e) { return Entier(e+ getValeur()); }
	Entier operator*(Entier e) { return Entier(e.getValeur() * getValeur()); }
	Entier operator*(int e) { return Entier(e * getValeur()); }
};
