#ifndef OPERATEUR_H
#define OPERATEUR_H
#include"operande.h"
#include <exception>
/*
 Classe pour gérer les exceptions sur les opérateurs
 Ces messages sont utile pour notre GUI (?)
*/
class OperateurException : public std::exception
{
    QString info;
public:
    OperateurException (QString in) : info(in) {}
    QString getInfo(){return info;}
    virtual const char* what() const throw()
      {
        return info.toStdString().c_str();
      }

};

class Operateur;

class OperationManager
{
    static OperationManager* man;
    static Operateur* lastOp;
    static std::vector<Litterale*> lastLits;
    OperationManager(){}
    ~OperationManager();
    void operator=(OperationManager& l);
    OperationManager(OperationManager& l);
public:
    static OperationManager& donnerInstance();
    static void libererInstance();
    static void sauvegarder(Operateur* o);
    static Operateur* getLastOp();
    static std::vector<Litterale*>::const_iterator getLastLitsBegin();
    static std::vector<Litterale*>::const_iterator getLastLitsEnd();

    static void add( Litterale* l);
};

class Operateur : public Operande
{
protected:
    QString symbole;
    unsigned int priority=0;
public:
    virtual ~Operateur(){}
    virtual void chargerContexte() = 0;
    virtual void resetContexte() = 0;
    void setSymbole(QString const symb){symbole=symb;}
    virtual void pushResultat(Litterale* res);
    virtual void operation();

    virtual Litterale* traitementOperateur() =0;
    virtual Litterale* traitementExpression(){return nullptr;}

    const QString getSymbole() const {return symbole;}

    void setPriority(unsigned int p){priority=p;}

    unsigned int getPriority()  const {return priority;}
};




class OperateurBinaire : public virtual Operateur{
 protected:
    Litterale* l1=nullptr;
    Litterale* l2=nullptr;
public:
    void chargerContexte();

    void resetContexte();
    virtual ~OperateurBinaire(){delete l1;delete l2;}

    OperateurBinaire():Operateur(){}
    OperateurBinaire(Litterale* lit1, Litterale* lit2):Operateur(),l1(lit1),l2(lit2){}
    Litterale* getl1(){return l1;}
    Litterale* getl2(){return l2;}
};

class OperateurUnaire  : public virtual Operateur{
protected:
   Litterale* l1=nullptr;
public:
   virtual ~OperateurUnaire(){delete l1;}
   void chargerContexte();
   void resetContexte();
   OperateurUnaire():Operateur(){}
   OperateurUnaire(Litterale* lit1):Operateur(),l1(lit1){}
   Litterale* getl1(){return l1;}
};

/*• On peut également appliquer l’ensemble des opérateurs numériques et logiques s’écrivant sous forme de lettres
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
exemple, la ligne de commande ’3+X’’9*Y’* a pour résultat ’(3+X)*9*Y’.*/

class OperateurPrefixe : public virtual Operateur{
   Litterale* traitementExpression();
public:
   virtual ~OperateurPrefixe(){}

};

class OperateurInfixe : public virtual Operateur{
    Litterale* traitementExpression();
public:
    virtual ~OperateurInfixe(){}
};


#endif // OPERATEUR_H
