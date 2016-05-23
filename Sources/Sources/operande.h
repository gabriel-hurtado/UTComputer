#include <string>
#include <sstream>
#include <exception>
#include <iostream>
#ifndef H_OPERANDE
#define H_OPERANDE

class Litterale;

class Operande
{

public:
	Operande() {}
	virtual ~Operande() {};
    virtual Litterale* traitement() = 0;

};

#endif
