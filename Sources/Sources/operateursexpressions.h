#ifndef OPERATEURSEXPRESSIONS_H
#define OPERATEURSEXPRESSIONS_H


#include"operateur.h"

namespace expression{

class OperateurExpression : public virtual Operateur
{
public:

    OperateurExpression(){}



};




/*
 * TODO
 *
• On peut aussi appliquer l’ensemble des opérateurs numériques et logiques binaires entre une littérale expression
et une littérale numérique. Si l’un des deux arguments n’est pas une littérale numérique, il est d’abord
transformé en littérale expression puis les règles précédentes sont appliquées.
*/


class OperateurEVAL : public OperateurUnaire, public OperateurExpression{

public:
   Litterale* traitementOperateur();

   OperateurEVAL():OperateurUnaire(){}

   OperateurEVAL(Litterale* l1):OperateurUnaire(l1){}


};



class OperateurSTO : public OperateurBinaire, public OperateurExpression{

public:
   Litterale* traitementOperateur();

   OperateurSTO():OperateurBinaire(){}

   OperateurSTO(Litterale* l1, Litterale* l2):OperateurBinaire(l1,l2){}

};



//a déclancher dès qu'on empile un atome
//soucis pour le REDO ?
class OperateurUserMade : public OperateurUnaire, public OperateurExpression{
public:
   Litterale* traitementOperateur();

   OperateurUserMade():OperateurUnaire(){}
   OperateurUserMade(Litterale* l1):OperateurUnaire(l1){}


};



}

#endif // OPERATEURSEXPRESSIONS_H
