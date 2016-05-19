#include "operande.h"
#include <string>
#include <sstream>

class Litterale : public Operande
{
public:
	Litterale() {}
	virtual ~Litterale() {};
	virtual const std::string afficher() = 0;

private:

};


class LitteraleSimple : public Litterale
{
public:
	LitteraleSimple() {}
	virtual ~LitteraleSimple() {};

private:

};

class LitteraleComplexe : public LitteraleSimple
{
public:
	LitteraleComplexe() {}
	virtual ~LitteraleComplexe() {};

private:

};

class LitteraleNumerique : public LitteraleComplexe
{
public:
	LitteraleNumerique() {}
	virtual ~LitteraleNumerique() {};

private:

};



