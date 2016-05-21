#include "operande.h"
#include "utils.h"
#include <string>
#include <sstream>
#include <exception>

class LitteraleException : public std::exception
{
	std::string info;
public:
	LitteraleException (std::string in) : info(in) {}
	const std::string	getMessage() { return info; }
};


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



