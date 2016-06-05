#ifndef LITTERALEEXCEPTION_H
#define LITTERALEEXCEPTION_H
#include "operande.h"
/*
 Classe pour gérer les exceptions sur les littérales
 Ces messages sont utile pour notre GUI (?)
*/

class LitteraleException : public std::exception
{
    QString info;
public:
    LitteraleException (QString in) : info(in) {}
    QString getInfo(){return info;}
    virtual const char* what() const throw()
    {
      return info.toStdString().c_str();
    }

};
#endif // LITTERALEEXCEPTION_H
