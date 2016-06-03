#include "operateursexpressions.h"
#include "litterales.h"
#include "variable.h"


namespace expression {



/* EVAL permet d’évaluer numériquement une littérale expression. Si elle comprend
au moins un atome qui ne correspond pas au nom d’une variable, l’évaluation n’a aucune effet et
un message en informe l’utilisateur. Si la littérale expression comprend au moins un atome qui correspond
à l’identificateur d’un programme, l’évaluation n’a aucun effet et un message d’erreur informe l’utilisateur.
Si tous les atomes de la littérales expression sont des identificateurs de variables, l’expression est évaluée
numériquement..*/
void OperateurEVAL::traitementOperateur(){
Expression* l1= estdeType<Expression>(l1);
 if(l1){
     l1->evaluer();

 }
    throw OperateurException("La littérale ne peut pas être évaluée");
}




/*À toute littérale peut être associée un identificateur en utilisant l’opérateur binaire STO. Le premier argument est
la littérale à stocker (qui peut être une littérale numérique, une littérale expression ou une littérale programme). Le
deuxième est une littérale expression ne comportant qu’un atome (i.e. un atome entre guillemets). L’atome devient
alors l’identificateur d’une variable s’il est associé à une littérale numérique ou l’identificateur d’un programme s’il
est associé à une littérale programme.
On ne peut pas utiliser un identificateur égal à un opérateur prédéfini. Une tentative dans ce sens provoque
l’affichage d’un message d’erreur. Si l’identificateur utilisé correspondait déjà à une autre variable ou un autre
programme, la variable ou le programme est ecrasé par cette nouvelle valeur.

*/
void OperateurSTO::traitementOperateur(){
    Expression* ex= estdeType<Expression>(l2);
    if(ex){
        Atome* at = nullptr; //ici besoin de récupérer l'atome si il est seul dans l'expression

        //vérifier que le nom de at n'est pas un opérateur prédéfini
        VariablesManager::donnerInstance().enregistrer(at->getNom(),ex);
    }
    throw OperateurException("Impossible de stocker dans cette littérale");

   }


/*
Quand un atome est utilisé sans guillemet :
• s’il est l’identicateur d’une variable, il est remplacé par la valeur de la littérale associée;
• s’il est l’identificateur d’un programme, il provoque l’évaluation (l’exécution) du programme.*/
void OperateurUserMade::traitementOperateur(){
    Atome* at = estdeType<Atome>(l1);
    if(at){
        Litterale* var=VariablesManager::donnerInstance().getVariable(at->getNom());
        Programme* prog=estdeType<Programme>(var);
        if(prog){
            prog->traitement();
        }
        else{
            p<<*var;
        }

    }
    throw OperateurException("Impossible d'éxécuter cette fonction sur ça !");

}


}
