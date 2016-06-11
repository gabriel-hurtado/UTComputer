

#include "litteralefactory.h"
#include "operateurfactory.h"

#include "mainwindow.h"

#include "operateursnumeriques.h"
#include "operateurslogiques.h"
#include "operateursexpressions.h"
#include "operateurspile.h"
#include "operateurscond.h"

int main(int argc,char* argv[]) {

    /*
        Littérales Updated on 02/06/16
    */
    LitteraleFactory::enregistrer(0,"[",new Programme(""),"]",new RecursiveEncapsulatorIdentifier("[","]"));
    LitteraleFactory::enregistrer(1,"'",new Expression(""),"'" ,new EncapsulatorIdentifier("'","'"));
    LitteraleFactory::enregistrerInfix(2,"$",new Complexe(*dynamic_cast<LitteraleNumerique*>(new Entier(1)),*dynamic_cast<LitteraleNumerique*>(new Entier(1))));
    LitteraleFactory::enregistrer(4,".",new Reelle(1,1));
    LitteraleFactory::enregistrerInfix(3,"/",new Rationnel(2,1));
    LitteraleFactory::enregistrer(INT_MAX-1,"Atome",new Atome("ERROR"));
    LitteraleFactory::enregistrer(INT_MAX,"Entier",new Entier(0));

    /*
        Opérateurs numériques Updated on 5/06/16
    */
    OperateurFactory::enregistrer("NEG",new numerique::OperateurNEG);
    OperateurFactory::enregistrer("+",new numerique::OperateurAddition);
    OperateurFactory::enregistrer("-",new numerique::OperateurSoustraction);
    OperateurFactory::enregistrer("/",new numerique::OperateurDivision);
    OperateurFactory::enregistrer("DIV",new numerique::OperateurDIV);
    OperateurFactory::enregistrer("MOD",new numerique::OperateurMOD);
    OperateurFactory::enregistrer("NUM",new numerique::OperateurNUM);
    OperateurFactory::enregistrer("DEN",new numerique::OperateurDEN);
    OperateurFactory::enregistrer("*",new numerique::OperateurMultiplication);
    OperateurFactory::enregistrer("IM",new numerique::OperateurIM);
    OperateurFactory::enregistrer("RE",new numerique::OperateurRE);
    OperateurFactory::enregistrer("$",new numerique::Operateur$);

    /*
        Opérateurs logiques Updated on 5/06/16
    */
    OperateurFactory::enregistrer("=",new logique::OperateurEgal);
    OperateurFactory::enregistrer("!=",new logique::OperateurDiff);
    OperateurFactory::enregistrer("<=",new logique::OperateurInfEgal);
    OperateurFactory::enregistrer(">=",new logique::OperateurSupEgal);
    OperateurFactory::enregistrer(">",new logique::OperateurSup);
    OperateurFactory::enregistrer("<",new logique::OperateurInf);
    OperateurFactory::enregistrer("AND",new logique::OperateurAND);
    OperateurFactory::enregistrer("OR",new logique::OperateurOR);
    OperateurFactory::enregistrer("NOT",new logique::OperateurNOT);

    /*
        Opérateurs pile Updated on 5/06/16
    */
    OperateurFactory::enregistrer("DUP",new op_pile::OperateurDUP);
    OperateurFactory::enregistrer("DROP",new op_pile::OperateurDROP);
    OperateurFactory::enregistrer("SWAP",new op_pile::OperateurSWAP);
    OperateurFactory::enregistrer("UNDO",new op_pile::OperateurUNDO);
    OperateurFactory::enregistrer("REDO",new op_pile::OperateurREDO);
    OperateurFactory::enregistrer("CLEAR",new op_pile::OperateurCLEAR);
    OperateurFactory::enregistrer("LASTOP",new op_pile::OperateurLASTOP);
    OperateurFactory::enregistrer("LASTARGS",new op_pile::OperateurLASTARGS);

    OperateurFactory::enregistrer("EDIT",new op_pile::OperateurEDIT);

    /*
        Opérateurs EXpression Updated on 5/06/16
    */
    OperateurFactory::enregistrer("EVAL",new expression::OperateurEVAL);
    OperateurFactory::enregistrer("STO",new expression::OperateurSTO);

    OperateurFactory::enregistrer("IFT",new conditionnel::OperateurIFT);



    QApplication app(argc, argv);

    MainWindow fenetre;
    fenetre.show();

    return app.exec();

    return 0;
}
