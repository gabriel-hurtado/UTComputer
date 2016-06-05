#ifndef PILE_H
#define PILE_H
#include "litterales.h"
#include <vector>


class MementoPile;
/*
    Manuel pour utiliser un objet "deque" :
    http://en.cppreference.com/w/cpp/container/deque
*/
/*
    Pile est l'Originator du Memento
*/
class GerantPile;

class PileException : public std::exception
{
    QString info;
public:
    PileException (QString in) : info(in) {}
    QString getInfo(){return info;}
    virtual const char* what() const throw()
      {
        return info.toStdString().c_str();
      }
};


class Pile : public QObject{
    Q_OBJECT

    std::vector<Litterale*> emP;//emP stands for "embedded Pile"
    static Pile* instancePile;
    unsigned int nbLitteraletoAffiche;

    /*made those method in private so the user can't use them*/
    Pile():nbLitteraletoAffiche(10){}
    Pile(const Pile& p);
    ~Pile(){}
    void operator=(const Pile&);

public:
    friend class MementoPile; //Help for the constructor of a MementoPile
    Pile& operator<<(Litterale& l);
    Pile& operator>>(Litterale*& l);
    void voirPile() const;
    void viderPile(){emP.clear();}
    static Pile& donnerInstance();
    static void libererInstance();
    //Méthodes pour le Memento
    MementoPile* saveInMemento() const;
    void restoreFromMemento(MementoPile* m);
    void UNDO();
    void REDO();
    void sauverPile();

    unsigned int getNbToAffiche(){return nbLitteraletoAffiche;}
    void setNbToAffiche(unsigned int i){nbLitteraletoAffiche=i;sendRegenerateVuePile();}



    /*
        Iterator sur la Pile
    */
    class iterator {
            std::vector<Litterale*>::iterator ite;
        public:
            iterator(std::vector<Litterale*>::iterator i = instancePile->emP.begin()):ite(i){}
            Litterale& operator*() const { return *(*ite); }
            bool operator!=(iterator it) const { return ite!=it.ite; }
            iterator& operator++(){ ++ite; return *this; }
        };
        iterator begin() { return emP.begin(); }
        iterator end() { return emP.end(); }

signals:
        void modificationEtat();
        void sendRegenerateVuePile();

};


/*
    Classe MementoPile :
        crée des objets qui contiennent une sauvegarde de la pile
*/
class MementoPile{
    std::vector<Litterale*> saved_emP;
public:
    friend class Pile; //Pour que la Pile puisse acceder au saved_emP d'un MementoPile (on casse ici l'encapsulation mais ces classes ne sont normalement pas utilisées par l'User)
    friend class GerantPile;//Pour que le GerantPile puisse acceder au saved_emP d'un Memento (on casse ici l'encapsulation mais ces classes ne sont normalement pas utilisées par l'User)
    MementoPile(const std::vector<Litterale* >& emP);
};

class GerantPile{
    unsigned int nombreMaxDeMementoUNDO;
    unsigned int nombreDeMementoUNDO;
    MementoPile** savedMementoUNDO;
    unsigned int nombreMaxDeMementoREDO;
    unsigned int nombreDeMementoREDO;
    MementoPile** savedMementoREDO;

    static GerantPile *instanceGerantPile;

    GerantPile(unsigned int nbMaxUNDO = 1,unsigned int nbMaxREDO=1);
    ~GerantPile();
    GerantPile(const GerantPile&);
    void operator=(const GerantPile& g);

public:
    friend class MementoPile;
    static GerantPile& donnerInstance();
    static void libererInstance();
    GerantPile& push_back_undo(MementoPile* l);
    MementoPile* pop_back_undo();
    GerantPile& push_back_redo(MementoPile* l);
    MementoPile* pop_back_redo();
    void sauverPile();
    void UNDO();
    void REDO();
    void clearREDO();

};
#endif // PILE_H
