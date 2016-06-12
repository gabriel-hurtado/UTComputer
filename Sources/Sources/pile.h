#ifndef PILE_H
#define PILE_H
#include "operande.h"
#include <QObject>

class QObject;

class Litterale;

class MementoPile;
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


    static Pile* instancePile;
    /**
     * @brief Permet de bloquer la sauvegarde de la pile si à true
    */
    static bool atomic_lock;

    unsigned int nbLitteraletoAffiche;
    /*made those method in private so the user can't use them*/
    Pile():nbLitteraletoAffiche(10){}
    Pile(const Pile& p);
    virtual ~Pile(){}
    void operator=(const Pile&);

<<<<<<< HEAD
=======
    /**
     * @brief le vector emP contient les litterales*
     *
    */
    std::vector<Litterale*> emP;//emP stands for "embedded Pile"
>>>>>>> a213724647143e7a4ec9c66baab10b8d6fe676e6

public:

    std::vector<Litterale*> emP;//emP stands for "embedded Pile"
    friend class MementoPile; //Help for the constructor of a MementoPile

    /**
     * @brief Unique méthode pour push une littérale* dans la pile.
     * @details Provoque une copie de la pile avant ajout, afin de pouvoir effectuer la commande UNDO\n
     * Enlève aussi tout les REDO, car ils ne sont plus cohérents après un ajout\n
     * Attention : La sauvegarde fonctionne uniquement si atomic_lock est à false;
     * @return Retourne une référence sur la pile pour effectuer des ajouts les uns à la suite des autres
     */
    Pile& operator<<(Litterale& l);

    /**
     * @brief Unique méthode pour pop une littérale* dans la pile.
     * @details Provoque une copie de la pile avant ajout, afin de pouvoir effectuer la commande UNDO\n
     * Attention : La sauvegarde fonctionne uniquement si atomic_lock est à false;
     * @return Retourne une référence sur la pile pour effectuer des retraits les uns à la suite des autres
     */
    Pile& operator>>(Litterale*& l);
    void voirPile() const;
    void viderPile(){emP.clear();
                     modificationEtat();}
    static Pile& donnerInstance();
    static void libererInstance();
    //Méthodes pour le Memento
    MementoPile* saveInMemento() const;
    void restoreFromMemento(MementoPile* m);

    /**
     * @brief Appelle la méthode UNDO du gérant de la pile, qui elle restaure l'état précédant de la pile
    */
    void UNDO();

    /**
     * @brief Appelle la méthode REDO du gérant de la pile, qui elle restaure l'état de la pile suivant le dernier UNDO
    */
    void REDO();
    void sauverPile();

    unsigned int getNbToAffiche(){return nbLitteraletoAffiche;}
    void setNbToAffiche(unsigned int i){nbLitteraletoAffiche=i;sendRegenerateVuePile();}

    /**
     * @brief Permet de selectionner l'état du verrou de la pile
     * @details true pour empécher la sauvegarde et false pour l'autoriser
    */
    static void setAtomicLock(bool v){atomic_lock = v;}
    MementoPile** savedMementoUNDO;
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
        /**
         * @brief Permet de signaler à la mainWindow un changement d'état de la pile, afin qu'elle puisse rafraichir l'affichage
         */
        void modificationEtat();

        /**
         * @brief Permet de signal à la mainWindow que le nombre d'objets à afficher à changé, et qu'il faut recréer la vue de la pile
        */
        void sendRegenerateVuePile();

};


/**
 * @class MementoPile
 * @brief Encapsule un vector de littérale, qui décrit un état de la pile
 *
*/
class MementoPile{
    std::vector<Litterale*> saved_emP;
public:
    friend class Pile; //Pour que la Pile puisse acceder au saved_emP d'un MementoPile (on casse ici l'encapsulation mais ces classes ne sont normalement pas utilisées par l'User)
    friend class GerantPile;//Pour que le GerantPile puisse acceder au saved_emP d'un Memento (on casse ici l'encapsulation mais ces classes ne sont normalement pas utilisées par l'User)
    MementoPile(const std::vector<Litterale* >& emP);
};

/**
 * @class GerantPile
 * @brief Classe gérant les différentes sauvegardes de la pile,
 * @details L'objet GerantPile est singleton et s'occupe de fonctionner les opérations UNO et REDO correctement sur la pile.
*/
class GerantPile{
    unsigned int nombreMaxDeMementoUNDO;
    unsigned int nombreDeMementoUNDO;
    MementoPile** savedMementoUNDO;
    unsigned int nombreMaxDeMementoREDO;
    unsigned int nombreDeMementoREDO;
    MementoPile** savedMementoREDO;

    static GerantPile *instanceGerantPile;

    GerantPile(unsigned int nbMaxUNDO = 1,unsigned int nbMaxREDO=1);
    virtual ~GerantPile();
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
    void seeUNDOList();
    void seeREDOList();

};
#endif // PILE_H
