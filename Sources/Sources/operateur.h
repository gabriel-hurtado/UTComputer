#ifndef OPERATEUR_H
#define OPERATEUR_H
#include"operande.h"
#include <exception>
/**
 Classe pour gérer les exceptions sur les opérateurs
 \bief Définition des opérateurs
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
    virtual ~OperationManager();
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


/** \class Operateur
   * \brief classe la plus abstraite des opérateurs
   *
   *  La classe definit le comportement et les attributs communs aux opérateurs
   */

class Operateur : public Operande
{
protected:
    QString symbole;
    unsigned int priority=0;
public:
    virtual ~Operateur(){}

    /**
        *  \brief Dépile le bon nombre le littérales
        *
        *  Methode qui permet de charger les littérales dans un opérateur
        *
        */
    virtual void chargerContexte() = 0;

    /**
        *  \brief Empile le bon nombre le littérales en cas d'echec
        *
        *  Methode qui permet de rempiler les littérales en cas d'erreur
        *
        */
    virtual void resetContexte() = 0;
    void setSymbole(QString const symb){symbole=symb;}
    virtual void pushResultat(Litterale* res);

    /**
     * \brief Traite l'opérateur, en lien avec la pile et le gestionnaire d'opérateurs
     * Commence par sauvegarder l'opérateur utilisé, à l'aide du gestionnaire d'opérations
     * Ensuite, charge le contexte, puis essaye de traiter les littérales comme des expressions
     * En cas d'échec, essaye de les considérer comme des littérales "non expression".
     * Si l'une des opérations à fonctionné, le résultat est mis sur la pile.
     * Si les deux ont échouées, on restaure le contexte.
     */
    virtual void operation();

    /**
     * @brief Traite les littérales comme des littérales "non expression"
     * @return un pointeur, sur le résultat, alloué dynamiquement, nullptr si aucun résultat n'est attendu.
     */
    virtual Litterale* traitementOperateur() =0;

    /**
     * @brief Traite les littérales comme des littérales expression
     * @return un pointeur, sur le résultat, alloué dynamiquement, nullptr en cas d'échec.
     */
    virtual Litterale* traitementExpression(){return nullptr;}

    const QString getSymbole() const {return symbole;}

    void setPriority(unsigned int p){priority=p;}

    unsigned int getPriority()  const {return priority;}
};




class OperateurBinaire : public virtual Operateur{
 protected:
    Litterale* l1=nullptr;
    Litterale* l2=nullptr;
public:
    void chargerContexte();

    void resetContexte();
    virtual ~OperateurBinaire();

    OperateurBinaire():Operateur(){}
    OperateurBinaire(Litterale* lit1, Litterale* lit2):Operateur(),l1(lit1),l2(lit2){}
    OperateurBinaire(const OperateurBinaire& b);
    OperateurBinaire& operator=(const OperateurBinaire&);
    Litterale* getl1(){return l1;}
    Litterale* getl2(){return l2;}
};

class OperateurUnaire  : public virtual Operateur{
protected:
   Litterale* l1=nullptr;
public:
   virtual ~OperateurUnaire();
   void chargerContexte();
   void resetContexte();
   OperateurUnaire():Operateur(){}
   OperateurUnaire(Litterale* lit1):Operateur(),l1(lit1){}
   OperateurUnaire(const OperateurUnaire&);
   OperateurUnaire& operator=(const OperateurUnaire&);
   Litterale* getl1(){return l1;}
};

/*• On peut également appliquer l’ensemble des opérateurs numériques et logiques s’écrivant sous forme de lettres
sur une littérale expression. Le résultat de l’opérateur OP unaire appliqué à la littérale expression ’EXP’ est
la littérale expression ’OP(EXP)’. Par exemple, la ligne de commande ’3+X’SIN a pour résultat SIN(3+X).
Le résultat de l’opérateur OP binaire appliqué aux littérales expressions ’EXP’ et ’EXP2’ est la littérale
expression ’OP(EXP1,EXP2)’.
• Le résultat de l’opérateur binaire utilisant un symbole (+, -, /, *, $) appliqué entre la littérale expression
’EXP1’ et la littérale expression ’EXP2’ renvoie un littérale expression composée des deux littérales initiales,
chacune entre parenthèses, les deux littérales étant séparées par le symbole. Par exemple, on obtient ’(EXP1
)+(EXP2)’ si l’opérateur est +. Les parenthèses autour des expressions EXP1 et/ou EXP2 sont omises dans
le résultat si tous les opérateurs non parenthésés dans l’expression ont la même priorité que l’opérateur. Les
opérateurs *, / ont une priorité supérieure à + et -. Les opérateurs *, / ont la même priorité entre eux. Les
opérateurs + et - ont la même priorité entre eux. Les opérateurs numériques ont priorité sur les opérateurs
logiques. Deux opérateurs qui ont la même priorité sont toujours évalués de la gauche vers la droite. Par
exemple, la ligne de commande ’3+X’’9*Y’* a pour résultat ’(3+X)*9*Y’.*/
/**
 * @brief Une classe utile pour les expressions
 * Permet la spécialisation d'un opérateur pour son traitement d'expressions
 */
class OperateurPrefixe : public virtual Operateur{
   Litterale* traitementExpression();
public:
   virtual ~OperateurPrefixe(){}

};

/**
 * @brief Une classe utile pour les expressions
 * Permet la spécialisation d'un opérateur pour son traitement d'expressions
 */
class OperateurInfixe : public virtual Operateur{
    Litterale* traitementExpression();
public:
    virtual ~OperateurInfixe(){}
};


#endif // OPERATEUR_H
