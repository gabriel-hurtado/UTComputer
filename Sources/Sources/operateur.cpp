#include "operateur.h"


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
    lastOp= o->getCopy();
    lastLits.clear();
}

void OperationManager::add(Litterale* l){
    lastLits.push_back(l);
}

Operateur* OperationManager::getLastOp(){
    if(lastOp!=nullptr)
    return lastOp->getCopy();
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
        Expression* ex1 = estdeType<Expression>(bin->getl1());
        Expression* ex2 = estdeType<Expression>(bin->getl2());

        QString symbol= bin->getSymbole();
        if(ex1 && !ex2)
        {
            ex2= new Expression("\""+bin->getl2()->toString()+"\"");

        }
        if(ex2 && !ex1)
        {
            ex1= new Expression("\""+bin->getl1()->toString()+"\"");

        }
        if(ex1 && ex2)
        {
           QString newExp = "\"("+ex1->getExpressionNoBorders()+")"+symbol+"("+ex2->getExpressionNoBorders()+")"+"\"";
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
           QString newExp = "\""+symbol+"("+ex1->getExpressionNoBorders()+")"+"\"";
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
      Expression* ex1 = estdeType<Expression>(bin->getl1());
      Expression* ex2 = estdeType<Expression>(bin->getl2());

      QString symbol= bin->getSymbole();
      if(ex1 && !ex2)
      {
          ex2= new Expression("\""+bin->getl2()->toString()+"\"");

      }
      if(ex2 && !ex1)
      {
          ex1= new Expression("\""+bin->getl1()->toString()+"\"");

      }
      if(ex1 && ex2)
      {
         QString newExp = "\""+symbol+"("+ex1->getExpressionNoBorders()+","+ex2->getExpressionNoBorders()+")"+"\"";
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
         QString newExp = "\""+symbol+"("+ex1->getExpressionNoBorders()+")"+"\"";
         return new Expression(newExp);
      }
       else
          return nullptr;
  }
  return nullptr;
}
