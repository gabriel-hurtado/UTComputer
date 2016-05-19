#include "litterales.h"
class Entier : public LitteraleNumerique {
	int valeur;
public:
	Entier(int v=0) :valeur(v) {}
	const int getValeur() { return valeur; }
	const std::string afficher() { return std::to_string(getValeur()); }
	~Entier() { LitteraleNumerique::~LitteraleNumerique(); }
};
