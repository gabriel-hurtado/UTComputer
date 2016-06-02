#ifndef OPERATEURSPILE_H
#define OPERATEURSPILE_H

#include"operateur.h"
#include<vector>
namespace op_pile{

class OperateurPile : public Operateur
{
public:

    OperateurPile(){}

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
                        }

    virtual void traitementOperateur() =0;
};


class OperateurBinaire : public OperateurPile{
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

    OperateurBinaire(){}
};

class OperateurUnaire  : public OperateurPile{
protected:
   Litterale* l1;
public:
   void chargerContexte(){p>>l1;
                         OperationManager::donnerInstance().add(l1);}

   void resetContexte(){if(l1) p<<*l1;}
   OperateurUnaire(){}
};



// empile une nouvelle littérale identique à celle du sommet de la pile.
class OperateurDUP : public OperateurUnaire{
public:
   void traitementOperateur(){Litterale* l2= l1->getCopy();
                              p<<*l1;
                              p<<*l2;
                             }

   OperateurDUP():OperateurUnaire(){}

   OperateurDUP* getCopy() {return new OperateurDUP(*this);}

};

//dépile la littérale au sommet de la pile.
class OperateurDROP : public OperateurUnaire{
public:
   void traitementOperateur(){delete l1;}

   OperateurDROP():OperateurUnaire(){}

   OperateurDROP* getCopy() {return new OperateurDROP(*this);}

};

//intervertit les deux derniers éléments empilés dans la pile.
class OperateurSWAP : public OperateurBinaire{
public:
   void traitementOperateur(){p<<*l2; p<<*l1;}

   OperateurSWAP():OperateurBinaire(){}

   OperateurSWAP* getCopy() {return new OperateurSWAP(*this);}
};

//rétablit l’état du calculateur avant la dernière opération.
class OperateurUNDO : public OperateurPile{
public:

    void traitementOperateur(){p.UNDO();}
    void chargerContexte(){}

    void resetContexte(){}

    OperateurUNDO(){}

     OperateurUNDO* getCopy() {return new OperateurUNDO(*this);}
};

//rétablit l’état du calculateur avant l’application de la dernière opération UNDO.
class OperateurREDO : public OperateurPile{
public:

    void traitementOperateur(){p.REDO();}
    void chargerContexte(){}

    void resetContexte(){}

    OperateurREDO(){}
     OperateurREDO* getCopy() {return new OperateurREDO(*this);}

};

//vide tous les éléments de la pile
class OperateurCLEAR : public OperateurPile{
public:

    void traitementOperateur(){p.viderPile();}
    void chargerContexte(){}

    void resetContexte(){}

    OperateurCLEAR(){}
     OperateurCLEAR* getCopy() {return new OperateurCLEAR(*this);}

};

class OperateurLASTOP: public Operateur{
public:

    void traitementOperateur(){OperationManager::donnerInstance().getLastOp()->operation();}
    void chargerContexte(){}

    void resetContexte(){}

    OperateurLASTOP(){}
     OperateurLASTOP* getCopy() {return new OperateurLASTOP(*this);}


     void operation(){
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

};

class OperateurLASTARGS: public Operateur{
public:

    void traitementOperateur(){
        std::vector<Litterale*>::const_iterator it1= OperationManager::donnerInstance().getLastLitsBegin();

        std::vector<Litterale*>::const_iterator it2= OperationManager::donnerInstance().getLastLitsEnd();
        do{
            p<<*(*it1);
            it1++;
        }while(it1!=it2);

    }
    void chargerContexte(){}

    void resetContexte(){}

    void operation(){
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


    OperateurLASTARGS(){}
     OperateurLASTARGS* getCopy() {return new OperateurLASTARGS(*this);}
};

}



#endif // OPERATEURSPILE_H
