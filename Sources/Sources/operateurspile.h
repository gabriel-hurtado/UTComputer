#ifndef OPERATEURSPILE_H
#define OPERATEURSPILE_H

#include"operateur.h"
#include "pile.h"
#include "mainwindow.h"
#include "litterales.h"
#include "operateursexpressions.h"
#include "variable.h"

namespace op_pile{

class OperateurPile : public virtual Operateur
{
public:

    OperateurPile():Operateur(){}
    Operateur* getCopy() const = 0;

};



// empile une nouvelle littérale identique à celle du sommet de la pile.
class OperateurDUP : public OperateurUnaire, public OperateurPile{

public:
   Litterale* traitementOperateur(){Litterale* l2= l1->getCopy();
                              Pile::donnerInstance()<<*l1->getCopy();
                              Pile::donnerInstance()<<*l2;
                              return nullptr;
                             }


   OperateurDUP():OperateurUnaire(){}
   Operateur* getCopy() const{return new OperateurDUP(*this);}

};

//dépile la littérale au sommet de la pile.
class OperateurDROP : public OperateurUnaire, public OperateurPile{

public:
   Litterale* traitementOperateur(){
                                     return nullptr;}

   OperateurDROP():OperateurUnaire(){}
   Operateur* getCopy() const{return new OperateurDROP(*this);}


};

//intervertit les deux derniers éléments empilés dans la pile.
class OperateurSWAP : public OperateurBinaire, public OperateurPile{

public:
   Litterale* traitementOperateur(){Pile::donnerInstance()<<*l2->getCopy(); Pile::donnerInstance()<<*l1->getCopy();
                                    return nullptr;}

   OperateurSWAP():OperateurBinaire(){}
   Operateur* getCopy() const{return new OperateurSWAP(*this);}

};

//rétablit l’état du calculateur avant la dernière opération.
class OperateurUNDO : public OperateurPile{

public:

    Litterale* traitementOperateur(){Pile::donnerInstance().UNDO();
                                     return nullptr;}

    void chargerContexte(){}

    void resetContexte(){}

    OperateurUNDO():OperateurPile(){}
    Operateur* getCopy() const{return new OperateurUNDO(*this);}

};

//rétablit l’état du calculateur avant l’application de la dernière opération UNDO.
class OperateurREDO : public OperateurPile{

public:

    Litterale* traitementOperateur(){Pile::donnerInstance().REDO();
                                     return nullptr;}

    void chargerContexte(){}

    void resetContexte(){}

    OperateurREDO():OperateurPile(){}
    Operateur* getCopy() const{return new OperateurREDO(*this);}

};

//vide tous les éléments de la pile
class OperateurCLEAR : public OperateurPile{

public:

    Litterale* traitementOperateur(){Pile::donnerInstance().viderPile();
                                     return nullptr;}

    void chargerContexte(){}

    void resetContexte(){}

    OperateurCLEAR():OperateurPile(){}
    Operateur* getCopy() const{return new OperateurCLEAR(*this);}

};

//dépile la littérale au sommet de la pile.
class OperateurFORGET : public OperateurUnaire{

public:
   Litterale* traitementOperateur(){  Expression* p=estdeType<Expression>(l1);

                                        if(p){
                                            QString val =p->getExpressionNoBorders();
                                            if(VariablesManager::getVariable(val))
                                            VariablesManager::donnerInstance().supprimer(val);

                                        }
                                        else{
                                            throw OperateurException("Error in forget");
                                        }
                                     return nullptr;}

   OperateurFORGET():OperateurUnaire(){}
   Operateur* getCopy() const{return new OperateurFORGET(*this);}


};

class OperateurEDIT : public Operateur{

public:
   Litterale* traitementOperateur(){
                                       MainWindow::getInstanceMainWindow()->openProgramWindow();
                                        return nullptr;
                                     }

   OperateurEDIT():Operateur(){}
   Operateur* getCopy() const{return new OperateurEDIT(*this);}
   void chargerContexte(){}
   void resetContexte(){}


};

class OperateurLASTOP: public Operateur{

public:

    Litterale* traitementOperateur(){Operateur* lastop =OperationManager::donnerInstance().getLastOp();
                               lastop->operation();
                                     return nullptr;}

    void chargerContexte(){}

    void resetContexte(){}

    OperateurLASTOP():Operateur(){}


     void  operation() override{
                      try{chargerContexte(); traitementOperateur();
                            }
                         catch(OperateurException op){
                        resetContexte();
                        throw OperateurException(op);
                             }
                          catch(PileException op){
                         resetContexte();
                         throw PileException(op);
                             }
                         }
     Operateur* getCopy() const{return new OperateurLASTOP(*this);}

};

class OperateurLASTARGS: public Operateur{

public:

    Litterale* traitementOperateur(){
        std::vector<Litterale*>::const_iterator it1= OperationManager::donnerInstance().getLastLitsBegin();

        std::vector<Litterale*>::const_iterator it2= OperationManager::donnerInstance().getLastLitsEnd();
        do{
            Litterale* tmp = *it1;
            Pile::donnerInstance()<<*(tmp->getCopy());
            it1++;
        }while(it1!=it2);
         return nullptr;
    }

    void chargerContexte(){}

    void resetContexte(){}

    void operation() override{
                     try{chargerContexte(); traitementOperateur(); OperationManager::donnerInstance().sauvegarder(estdeType<Operateur>(this));
                        }
                        catch(OperateurException op){
                       resetContexte();
                       throw OperateurException(op);
                            }
                         catch(PileException op){
                        resetContexte();
                        throw PileException(op);
                            }
                        }
    Operateur* getCopy() const{return new OperateurLASTARGS(*this);}


    OperateurLASTARGS():Operateur(){}
};

}



#endif // OPERATEURSPILE_H
