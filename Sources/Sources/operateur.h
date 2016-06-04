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

class Operateur : public Operande
{
    static QString symbole;
public:

    Operateur(){}
    static QString getSymbole(){return symbole;}
    virtual void chargerContexte() = 0;
    virtual void resetContexte() = 0;
    virtual Operateur* getCopy()=0;
    virtual void pushResultat(Litterale* res) {Pile::donnerInstance()<<(*res);}
    virtual void operation()=0;
};

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



#endif // OPERATEUR_H
