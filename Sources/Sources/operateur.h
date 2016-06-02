#ifndef OPERATEUR_H
#define OPERATEUR_H
#include"operande.h"

#include"pile.h"



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
 protected:
    Pile& p = Pile::donnerInstance();
public:

    Operateur(){}
    static QString getSymbole(){return symbole;}
    virtual void chargerContexte() = 0;
    virtual void resetContexte() = 0;
    virtual Operateur* getCopy()=0;
    virtual void pushResultat(Litterale* res) {p<<(*res);}
    void operation(){
                     try{chargerContexte(); Litterale* res=traitementOperateur(); pushResultat(res); }
                        catch(OperateurException op){
                       resetContexte();
                       //throw OperateurException(op);
                            }
                         catch(PileException op){
                        resetContexte();
                        //throw PileException(op);
                            }
                        }

    virtual Litterale* traitementOperateur() =0;
};

#endif // OPERATEUR_H
