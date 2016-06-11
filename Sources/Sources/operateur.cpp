#include "operateur.h"
#include "controleur.h"
#include "litterales.h"
#include "litteraleexception.h"
#include"pile.h"

// Définitions de la classe OperateurBinaire

unsigned int Operande::nb_alloc=0;

OperateurBinaire::OperateurBinaire(Litterale* lit1, Litterale* lit2):Operateur(),l1(lit1->getCopy()),l2(lit2->getCopy()){}

void OperateurBinaire::chargerContexte(){
                        l1=nullptr;l2=nullptr;
                        Pile::donnerInstance()>>l2;
                        Pile::donnerInstance()>>l1;
                        OperationManager::donnerInstance().add(l1->getCopy());
                        OperationManager::donnerInstance().add(l2->getCopy());
}

void OperateurBinaire::resetContexte(){if(l1) Pile::donnerInstance()<<*l1;
                     if(l2)  Pile::donnerInstance()<<*l2;}

OperateurBinaire::~OperateurBinaire(){delete l1;delete l2;}

OperateurBinaire::OperateurBinaire(const OperateurBinaire &b){
    if(b.l1)
        l1=estdeType<Litterale>(b.l1->getCopy());
    if(b.l2)
        l2=estdeType<Litterale>(b.l2->getCopy());
}
OperateurBinaire& OperateurBinaire::operator =(const OperateurBinaire& b){
    l1=b.l1->getCopy();
    l2=b.l2->getCopy();
    return *this;
}

// Définitions de la classe Operateur

void Operateur::pushResultat(Litterale* res) {Pile::donnerInstance()<<(*res);}
void Operateur::operation(){
                 try{
                        OperationManager::donnerInstance().sauvegarder(estdeType<Operateur>(this));
                        chargerContexte();Litterale* resExp = traitementExpression();
                        Litterale* res;
                        if(!resExp) res =traitementOperateur();
                        else   res=resExp;
                        if(res) pushResultat(res);
                    }
                 catch(OperateurException op){
                   resetContexte();
                   throw OperateurException(op);
                 }
                 catch(PileException op){
                   resetContexte();
                   throw PileException(op);
                 }
                 catch(LitteraleException& op){
                   resetContexte();
                   throw LitteraleException(op);
                 }
}

//Définitions de la classe OperateurUnaire
void OperateurUnaire::chargerContexte(){
                      l1=nullptr;
                      Pile::donnerInstance()>>l1;
                      OperationManager::donnerInstance().add(l1->getCopy());}

void OperateurUnaire::resetContexte(){if(l1) Pile::donnerInstance()<<*l1;}

OperateurUnaire::OperateurUnaire(Litterale* lit1):Operateur(),l1(lit1->getCopy()){}

OperateurUnaire::~OperateurUnaire(){delete l1;}

OperateurUnaire::OperateurUnaire(const OperateurUnaire &b){
    l1=b.l1->getCopy();
}
OperateurUnaire& OperateurUnaire::operator =(const OperateurUnaire& b){
    l1=b.l1->getCopy();
    return *this;
}

//fonctions de opération manager

OperationManager* OperationManager::man= nullptr;
Operateur* OperationManager::lastOp=nullptr;
std::vector<Litterale*> OperationManager::lastLits=std::vector<Litterale*>();
OperationManager::~OperationManager(){
    man=nullptr;
    delete lastOp;
    lastLits.clear();
}

OperationManager& OperationManager::donnerInstance(){
    if(man==nullptr)
        man= new OperationManager();
    return *man;
}

void OperationManager::libererInstance(){
    delete man;
}

void OperationManager::sauvegarder( Operateur* o){
    lastOp = o->getCopy();
    for(Litterale* l : lastLits){
        delete l;
    }
    lastLits.clear();
}

void OperationManager::add(Litterale* l){
    lastLits.push_back(l);
}

Operateur* OperationManager::getLastOp(){
    if(lastOp!=nullptr)
    return lastOp;
    throw OperateurException("Pas d'opérateur sauvegardé");
}

std::vector<Litterale*>::const_iterator OperationManager::getLastLitsBegin(){
    if(!lastLits.empty()){
        std::vector<Litterale*>::const_iterator it =lastLits.begin();
        return it;
    }
    throw OperateurException("Pas de littérales sauvegardées");
}

std::vector<Litterale*>::const_iterator OperationManager::getLastLitsEnd(){
    if(!lastLits.empty()){
        std::vector<Litterale*>::const_iterator it =lastLits.end();
        return it;
    }
    throw OperateurException("Pas de littérales sauvegardées");
}

//fonctions de gestion des littérales expressions

Litterale* OperateurInfixe::traitementExpression(){
    OperateurBinaire* bin = estdeType<OperateurBinaire>(this);
    if(bin){
        Expression* ex1 = estdeType<Expression>(bin->getl1()->getCopy());
        Expression* ex2 = estdeType<Expression>(bin->getl2()->getCopy());

        QString symbol= bin->getSymbole();
        if(ex1 && !ex2)
        {
            delete ex2;
            ex2= new Expression("\'"+bin->getl2()->toString()+"\'");

        }
        if(ex2 && !ex1)
        {
            delete ex1;
            ex1= new Expression("\'"+bin->getl1()->toString()+"\'");

        }
        if(ex1 && ex2)
        {
           QString firstPart="("+ex1->getExpressionNoBorders()+")";
           firstPart = Controleur::ParenthesisCleaner(firstPart,bin->getPriority());

           QString secondPart="("+ex2->getExpressionNoBorders()+")";
           secondPart = Controleur::ParenthesisCleaner(secondPart,bin->getPriority());

           QString newExp = "\'"+firstPart+symbol+secondPart+"\'";

           delete ex1;
           delete ex2;

           return new Expression(newExp);
        }

        else
           return nullptr;

    }
    OperateurUnaire* un = estdeType<OperateurUnaire>(this);
    if(un)
    {
        Expression* ex1 = estdeType<Expression>(un->getl1());
        if(ex1)
        {
           QString symbol= un->getSymbole();
           QString newExp = "'"+symbol+"("+ex1->getExpressionNoBorders()+")"+"'";
           return new Expression(newExp);
        }
         else
            return nullptr;
    }
    return nullptr;
}

Litterale* OperateurPrefixe::traitementExpression(){
  OperateurBinaire* bin = estdeType<OperateurBinaire>(this);
  if(bin){
      Expression* ex1 = estdeType<Expression>(bin->getl1()->getCopy());
      Expression* ex2 = estdeType<Expression>(bin->getl2()->getCopy());

      QString symbol= bin->getSymbole();
      if(ex1 && !ex2)
      {
          delete ex2;
          ex2= new Expression("'"+bin->getl2()->toString()+"'");

      }
      if(ex2 && !ex1)
      {
          delete ex2;
          ex1= new Expression("'"+bin->getl1()->toString()+"'");

      }
      if(ex1 && ex2)
      {
         QString newExp = "'"+symbol+"("+ex1->getExpressionNoBorders()+","+ex2->getExpressionNoBorders()+")"+"'";
         delete ex1;
         delete ex2;
         return new Expression(newExp);
      }

      else
         return nullptr;

  }
  OperateurUnaire* un = estdeType<OperateurUnaire>(this);
  if(un)
  {
      Expression* ex1 = estdeType<Expression>(un->getl1());
      if(ex1)
      {
         QString symbol= un->getSymbole();
         QString newExp = "'"+symbol+"("+ex1->getExpressionNoBorders()+")"+"'";
         return new Expression(newExp);
      }
       else
          return nullptr;
  }
  return nullptr;
}
