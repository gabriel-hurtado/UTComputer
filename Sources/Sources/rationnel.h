#include "litterales.h"

class Rationnel : public LitteraleNumerique
{
	int numerateur;
	int denominateur;
public:
	Rationnel(int n=0, int d=1){
		//implementation of the creator
		}
	~Rationnel(){ LitteraleNumerique::~LitteraleNumerique(); }
	const int getNumerateur() { return numerateur; }
	const int getDenominator() { return denominateur; }
	const std::string afficher() { std::stringstream st;
	st << getNumerateur() << "/" << getDenominator();
	return st.str();
	}

};