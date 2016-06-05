#ifndef OPERATEUR_H
#define OPERATEUR_H
#include"operande.h"

#include"pile.h"
#include<vector>

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
public:

    Operateur(){}
    virtual void chargerContexte() = 0;
    virtual void resetContexte() = 0;
    virtual Operateur* getCopy()=0;
    virtual void pushResultat(Litterale* res) {Pile::donnerInstance()<<(*res);}
    void operation(){
                     try{OperationManager::donnerInstance().sauvegarder(estdeType<Operateur>(this));
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

    virtual Litterale* traitementOperateur() =0;
    Litterale* traitementExpression(){return nullptr;}


};




class OperateurBinaire : public virtual Operateur{
 protected:
    Litterale* l1=nullptr;
    Litterale* l2=nullptr;
public:
    void chargerContexte(){Pile::donnerInstance()>>l2;
                           Pile::donnerInstance()>>l1;
                          OperationManager::donnerInstance().add(l1);
                          OperationManager::donnerInstance().add(l2);}

    void resetContexte(){if(l1) Pile::donnerInstance()<<*l1;
                         if(l2)  Pile::donnerInstance()<<*l2;}

    OperateurBinaire(){}
    OperateurBinaire(Litterale* lit1, Litterale* lit2):l1(lit1),l2(lit2){}
};

class OperateurUnaire  : public virtual Operateur{
protected:
   Litterale* l1=nullptr;
public:
   void chargerContexte(){Pile::donnerInstance()>>l1;
                         OperationManager::donnerInstance().add(l1);}

   void resetContexte(){if(l1) Pile::donnerInstance()<<*l1;}
   OperateurUnaire(){}
   OperateurUnaire(Litterale* lit1):l1(lit1){}
};

class OperateurPrefixe : public virtual Operateur{
   Litterale* traitementExpression(){return nullptr;}

};

class OperateurInfixe : public virtual Operateur{
    Litterale* traitementExpression(){return nullptr;}
};


#endif // OPERATEUR_H
