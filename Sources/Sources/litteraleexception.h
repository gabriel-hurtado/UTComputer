#ifndef LITTERALEEXCEPTION_H
#define LITTERALEEXCEPTION_H
#include "operande.h"
#include <exception>

/*
 Classe pour gérer les exceptions sur les littérales
*/

class LitteraleException : public std::exception
{
    QString info;
    QString litType;
public:
    LitteraleException (QString in,QString type) : info(in),litType(type) {}
    QString getInfo() const {return info;}

    QString getType() const {return litType;}
    virtual const char* what() const throw()
    {
      return info.toStdString().c_str();
    }

};
#endif // LITTERALEEXCEPTION_H
