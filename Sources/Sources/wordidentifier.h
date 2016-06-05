#ifndef WORIDENTIFIER_H
#define WORIDENTIFIER_H
#include "litteraleexception.h"

/*
    Classe contenant la statégie d'identification à adopter
*/
struct SelectedPosition{
    QString::iterator it_debut;
    QString::iterator it_fin;
public:
    SelectedPosition(const QString::iterator& itleft,const QString::iterator& itright):it_debut(itleft),it_fin(itright){}
};
/*
    Version générique de l'identifieur, va jusqu'au prochain espace.
*/
class WordIdentifier{
public:
    WordIdentifier(){}
    virtual ~WordIdentifier(){}
    virtual void WordPosition(QString& s, SelectedPosition& Select);
    virtual bool WordGuesser(QString);
};

/*
    Pour des encapsulateurs comme des expressions
*/
class EncapsulatorIdentifier: public WordIdentifier{
    QString rightDelimiter;
    QString leftDelimiter;
public:
    EncapsulatorIdentifier(QString lD="",QString rD=""):rightDelimiter(rD),leftDelimiter(lD){}
    void WordPosition(QString& s, SelectedPosition& Select);
    bool WordGuesser(QString);
    void setRightDelimiter(QString s){rightDelimiter = s;}
    void setLeftDelimiter(QString s){leftDelimiter = s;}

};
/*
    Pour des encapsulateurs réccursifs, comme des programmes
*/
class RecursiveEncapsulatorIdentifier: public WordIdentifier{
    QString rightDelimiter;
    QString leftDelimiter;
public:
    RecursiveEncapsulatorIdentifier(QString lD="",QString rD=""):rightDelimiter(rD),leftDelimiter(lD){}
    void WordPosition(QString& s, SelectedPosition& Select);
    bool WordGuesser(QString);
    void setRightDelimiter(QString s){rightDelimiter = s;}
    void setLeftDelimiter(QString s){leftDelimiter = s;}
};
#endif // WORIDENTIFIER_H
