#ifndef OPERATEURSEXPRESSIONS_H
#define OPERATEURSEXPRESSIONS_H


#include"operateur.h"
namespace expression{

class OperateurExpression : public Operateur
{
public:

    OperateurExpression(){}

    virtual void traitementOperateur() =0;

    void operation(){
                     try{OperationManager::donnerInstance().sauvegarder(estdeType<Operateur>(this));
                        chargerContexte(); traitementOperateur(); }
                        catch(OperateurException op){
                       resetContexte();
                       throw OperateurException(op);
                            }
                         catch(PileException op){
                        resetContexte();
                        throw PileException(op);
                            }
                        catch(LitteraleException op){
                       resetContexte();
                       throw LitteraleException(op);
                        }
                        }

};


class OperateurBinaire : public OperateurExpression{
 protected:
    Litterale* l1;
    Litterale* l2;
public:
    void chargerContexte(){p>>l2;
                           p>>l1;
                          OperationManager::donnerInstance().add(l1);
                          OperationManager::donnerInstance().add(l2);}

    void resetContexte(){if(l1) p<<*l1;
                         if(l2)  p<<*l2;}

    OperateurBinaire(Litterale* li1, Litterale* li2):l1(li1),l2(li2){}
};

class OperateurUnaire  : public OperateurExpression{
protected:
   Litterale* l1;
public:
   void chargerContexte(){p>>l1;
                         OperationManager::donnerInstance().add(l1);}

   void resetContexte(){if(l1) p<<*l1;}
   OperateurUnaire(Litterale* lit1):l1(lit1){}
};


/*
 * TODO
 *
• On peut également appliquer l’ensemble des opérateurs numériques et logiques s’écrivant sous forme de lettres
sur une littérale expression. Le résultat de l’opérateur OP unaire appliqué à la littérale expression ’EXP’ est
la littérale expression ’OP(EXP)’. Par exemple, la ligne de commande ’3+X’SIN a pour résultat SIN(3+X).
Le résultat de l’opérateur OP binaire appliqué aux littérales expressions ’EXP’ et ’EXP2’ est la littérale
expression ’OP(EXP1,EXP2)’.
• Le résultat de l’opérateur binaire utilisant un symbole (+, -, /, *, $) appliqué entre la littérale expression
’EXP1’ et la littérale expression ’EXP2’ renvoie un littérale expression composée des deux littérales initiales,
chacune entre parenthèses, les deux littérales étant séparées par le symbole. Par exemple, on obtient ’(EXP1
)+(EXP2)’ si l’opérateur est +. Les parenthèses autour des expressions EXP1 et/ou EXP2 sont omises dans
le résultat si tous les opérateurs non parenthésés dans l’expression ont la même priorité que l’opérateur. Les
opérateurs *, / ont une priorité supérieure à + et -. Les opérateurs *, / ont la même priorité entre eux. Les
opérateurs + et - ont la même priorité entre eux. Les opérateurs numériques ont priorité sur les opérateurs
logiques. Deux opérateurs qui ont la même priorité sont toujours évalués de la gauche vers la droite. Par
exemple, la ligne de commande ’3+X’’9*Y’* a pour résultat ’(3+X)*9*Y’.
• On peut aussi appliquer l’ensemble des opérateurs numériques et logiques binaires entre une littérale expression
et une littérale numérique. Si l’un des deux arguments n’est pas une littérale numérique, il est d’abord
transformé en littérale expression puis les règles précédentes sont appliquées.
*/


class OperateurEVAL : public OperateurUnaire{
public:
   void traitementOperateur();

   OperateurEVAL(Litterale* l1):OperateurUnaire(l1){}

   OperateurEVAL* getCopy() {return new OperateurEVAL(*this);}

};



class OperateurSTO : public OperateurBinaire{
public:
   void traitementOperateur();

   OperateurSTO(Litterale* l1, Litterale* l2):OperateurBinaire(l1,l2){}

   OperateurSTO* getCopy() {return new OperateurSTO(*this);}

};



//a déclancher dès qu'on empile un atome
class OperateurUserMade : public OperateurUnaire{
public:
   void traitementOperateur();

   OperateurUserMade(Litterale* l1):OperateurUnaire(l1){}

   OperateurUserMade* getCopy() {return new OperateurUserMade(*this);}

};



}

#endif // OPERATEURSEXPRESSIONS_H
