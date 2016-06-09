#ifndef OPERATEURSPILE_H
#define OPERATEURSPILE_H

#include"operateur.h"
#include "pile.h"

namespace op_pile{

class OperateurPile : public virtual Operateur
{
public:

    OperateurPile():Operateur(){}

};



// empile une nouvelle littérale identique à celle du sommet de la pile.
class OperateurDUP : public OperateurUnaire, public OperateurPile{

public:
   Litterale* traitementOperateur(){Litterale* l2= l1->getCopy();
                              Pile::donnerInstance()<<*l1;
                              Pile::donnerInstance()<<*l2;
                              return nullptr;
                             }


   OperateurDUP():OperateurUnaire(){}


};

//dépile la littérale au sommet de la pile.
class OperateurDROP : public OperateurUnaire, public OperateurPile{

public:
   Litterale* traitementOperateur(){delete l1;
                                     return nullptr;}

   OperateurDROP():OperateurUnaire(){}


};

//intervertit les deux derniers éléments empilés dans la pile.
class OperateurSWAP : public OperateurBinaire, public OperateurPile{

public:
   Litterale* traitementOperateur(){Pile::donnerInstance()<<*l2; Pile::donnerInstance()<<*l1;
                                    return nullptr;}

   OperateurSWAP():OperateurBinaire(){}

};

//rétablit l’état du calculateur avant la dernière opération.
class OperateurUNDO : public OperateurPile{

public:

    Litterale* traitementOperateur(){Pile::donnerInstance().UNDO();
                                     return nullptr;}

    void chargerContexte(){}

    void resetContexte(){}

    OperateurUNDO():OperateurPile(){}

};

//rétablit l’état du calculateur avant l’application de la dernière opération UNDO.
class OperateurREDO : public OperateurPile{

public:

    Litterale* traitementOperateur(){Pile::donnerInstance().REDO();
                                     return nullptr;}

    void chargerContexte(){}

    void resetContexte(){}

    OperateurREDO():OperateurPile(){}

};

//vide tous les éléments de la pile
class OperateurCLEAR : public OperateurPile{

public:

    Litterale* traitementOperateur(){Pile::donnerInstance().viderPile();
                                     return nullptr;}

    void chargerContexte(){}

    void resetContexte(){}

    OperateurCLEAR():OperateurPile(){}

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

};

class OperateurLASTARGS: public Operateur{

public:

    Litterale* traitementOperateur(){
        std::vector<Litterale*>::const_iterator it1= OperationManager::donnerInstance().getLastLitsBegin();

        std::vector<Litterale*>::const_iterator it2= OperationManager::donnerInstance().getLastLitsEnd();
        do{
            Pile::donnerInstance()<<*(*it1);
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


    OperateurLASTARGS():Operateur(){}
};

}



#endif // OPERATEURSPILE_H
