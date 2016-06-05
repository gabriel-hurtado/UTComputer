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

   OperateurEVAL(){}

   OperateurEVAL(Litterale* l1):OperateurUnaire(l1){}

   OperateurEVAL* getCopy() {return new OperateurEVAL(*this);}

};



class OperateurSTO : public OperateurBinaire, public OperateurExpression{
public:
   Litterale* traitementOperateur();

   OperateurSTO(){}

   OperateurSTO(Litterale* l1, Litterale* l2):OperateurBinaire(l1,l2){}

   OperateurSTO* getCopy() {return new OperateurSTO(*this);}

};



//a déclancher dès qu'on empile un atome
//soucis pour le REDO ?
class OperateurUserMade : public OperateurUnaire, public OperateurExpression{
public:
   Litterale* traitementOperateur();

   OperateurUserMade(){}
   OperateurUserMade(Litterale* l1):OperateurUnaire(l1){}

   OperateurUserMade* getCopy() {return new OperateurUserMade(*this);}

};



}

#endif // OPERATEURSEXPRESSIONS_H
