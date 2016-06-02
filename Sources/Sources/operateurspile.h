#ifndef OPERATEURSPILE_H
#define OPERATEURSPILE_H



namespace op_pile{

class OperateurPile : public Operateur
{
public:

    OperateurPile(){}

    void operation(){
                     try{chargerContexte(); traitementOperateur(); }
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


class OperateurBinaire : public OperateurPile{
 protected:
    Litterale* l1;
    Litterale* l2;
public:
    void chargerContexte(){p>>l2;
                           p>>l1;}

    void resetContexte(){if(l1) p<<*l1;
                         if(l2)  p<<*l2;}

    OperateurBinaire(){}
};

class OperateurUnaire  : public OperateurPile{
protected:
   Litterale* l1;
public:
   void chargerContexte(){p>>l1;}

   void resetContexte(){if(l1) p<<*l1;}
   OperateurUnaire(){}
};

}

// empile une nouvelle littérale identique à celle du sommet de la pile.
class OperateurDUP : public OperateurUnaire{
public:
   void traitementOperateur(){Litterale* l2= l1->getCopy();
                              p<<l1;
                              p<<l2;}

   OperateurDUP():OperateurUnaire(){}

   OperateurDUP* getCopy() {return new OperateurDUP(*this);}

};

//dépile la littérale au sommet de la pile.
class OperateurDROP : public OperateurUnaire{
public:
   void traitementOperateur(){delete l1;}

   OperateurDROP():OperateurUnaire(){}

   OperateurDROP* getCopy() {return new OperateurDUP(*this);}

};

//intervertit les deux derniers éléments empilés dans la pile.
class OperateurSWAP : public OperateurBinaire{
public:
   void traitementOperateur(){p<<12; p<<l1;}

   OperateurSWAP():OperateurBinaire(){}

   OperateurSWAP* getCopy() {return new OperateurAddition(*this);}
};

//rétablit l’état du calculateur avant la dernière opération.
class OperateurUNDO : public OperateurPile{
public:

    void traitementOperateur(){p.UNDO();}
    void chargerContexte(){}

    void resetContexte(){}

    OperateurUNDO(){}

};

//rétablit l’état du calculateur avant l’application de la dernière opération UNDO.
class OperateurREDO : public OperateurPile{
public:

    void traitementOperateur(){p.REDO();}
    void chargerContexte(){}

    void resetContexte(){}

    OperateurREDO(){}

};

//vide tous les éléments de la pile
class OperateurCLEAR : public OperateurPile{
public:

    void traitementOperateur(){p.viderPile();}
    void chargerContexte(){}

    void resetContexte(){}

    OperateurCLEAR(){}

};

/*
 * TODO
• LASTOP : applique le dernier opérateur utilisé.
• LASTARGS : empile les littérales utilisées pour la dernière opération.*/



#endif // OPERATEURSPILE_H
