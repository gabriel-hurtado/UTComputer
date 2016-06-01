#ifndef VARIABLE_H
#define VARIABLE_H
#include "litterales.h"
#include <map>


class VariableException : public std::exception
{
    QString info;
public:
    VariableException (QString in) : info(in) {}
    QString getInfo(){return info;}
    virtual const char* what() const throw()
    {
      return info.toStdString().c_str();
    }

};


class Variable{
    Operande* lit;
    public:
        Variable(Operande* l):lit(l){}
        Operande& getValeur() const{return *lit;}

};

class VariablesManager{
    static QMap<QString, Variable*> var_map;
    static VariablesManager* instance;
    VariablesManager(){}
    ~VariablesManager();
    void operator=(VariablesManager& l);
    VariablesManager(VariablesManager& l);

public:
    /*Méthodes du singleton*/
    static VariablesManager& donnerInstance();
    static void libererInstance();

    //Pour enregistrer des nouvelles variables
    static void enregistrer(const QString& nom,Variable* obj);
    static void supprimer(const QString& nom);
    static Variable& getVariable(const QString& nom);
};

#endif // VARIABLE_H
