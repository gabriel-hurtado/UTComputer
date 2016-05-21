#include "entier.h"
class Rationnel : public LitteraleNumerique
{
	int numerateur;
	int denominateur;
public:
	Rationnel(int n, int d=1){
		if (d == 0)
			throw LitteraleException("Le dénominateur ne peut être nul !");	
		else {
			int pg = pgcd(n, d);
			n = n / pg;
			d = d / pg;
			numerateur = n;
			denominateur = d;
			}
		}
	Rationnel(const Entier& n, const Entier& d) { Rationnel(n.getValeur(), d.getValeur()); }
	~Rationnel(){ LitteraleNumerique::~LitteraleNumerique(); }
	const int getNumerateur() const{ return numerateur; }
	const int getDenominator() const{ return denominateur; }
	const std::string afficher() { std::stringstream st;
									st << getNumerateur() << "/" << getDenominator();
									return st.str();
									}
	Rationnel operator+(const Rationnel& r) {	int newDen=r.getDenominator()*getDenominator();
												int newNum = r.getNumerateur()*getDenominator()+getNumerateur()*r.getDenominator();
												return Rationnel(newDen, newNum);
											}
	Rationnel operator*(const Rationnel& r) {
												int newDen = r.getDenominator()*getDenominator();
												int newNum = r.getNumerateur()*getNumerateur();
												return Rationnel(newDen, newNum);
											}

};