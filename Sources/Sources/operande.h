#ifndef H_OPERANDE
#define H_OPERANDE
#include <QString>
#include <sstream>
#include <iostream>
#include <math.h>
#include <vector>
#include <QStack>
#include "utils.h"
#include <iostream>
#include <typeinfo>
class Litterale;

class Operande
{
    static unsigned int nb_alloc;
public:
    Operande() {
        std::cout << nb_alloc << "allocating operande " << static_cast<void*>(this)<<std::endl;

        nb_alloc++;

    }
    virtual ~Operande() {
        std::cout << nb_alloc << "destroying " << static_cast<void*>(this)<<std::endl;
        nb_alloc--;
    }

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
