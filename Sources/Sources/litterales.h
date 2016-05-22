#include "operande.h"

/*
 Classe pour gérer les exceptions sur les littérales
 Ces messages sont utile pour notre GUI (?)
*/
class LitteraleException : public std::exception
{
	std::string info;
public:
	LitteraleException (std::string in) : info(in) {}
	const std::string	getMessage() { return info; }
};

/*Classes "Litterales" abstraites*/

class Litterale : public Operande
{
public:
	Litterale() {}
	virtual ~Litterale() {};
    /*Template method pour afficher utilisant toString()*/
    void afficher(std::ostream& f=std::cout){f<<toString();}
    virtual const std::string toString() const = 0;

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

/*
    Fonction Template pour connaitre les types des objets :
    L'objet de type T est-il de type L ?
*/
template<typename T,typename L> bool estdeType(T* Tobj){
    L* Lobj;
    if(Lobj=dynamic_cast<L*>(Tobj))
        return true;
    return false;

}


