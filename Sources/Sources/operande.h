#ifndef H_OPERANDE
#define H_OPERANDE
#include <QString>
#include <sstream>
#include <iostream>
#include <math.h>
#include <vector>
#include <QStack>
#include "utils.h"

class Litterale;

class Operande
{

public:
    Operande() {}
    virtual ~Operande() {}

};

/*
    Fonction Template pour connaitre les types des objets :
    L'objet de type T est-il de type L ?
*/

/** \brief template pour simplifier les dynamic cast, tout en les limitant à des opérandes.
  *
 */
template<typename L> L* estdeType(Operande* Tobj){
    L* Lobj;
    if(Tobj==nullptr)

        return nullptr;
    if((Lobj=dynamic_cast<L*>(Tobj)))
        return Lobj;
    return nullptr;

}
#endif
