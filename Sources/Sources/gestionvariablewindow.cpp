#include "gestionvariablewindow.h"
#include "ui_gestionvariablewindow.h"
#include "litteraleexception.h"
#include "litteralefactory.h"
#include "variable.h"
#include "litterales.h"
#include "mainwindow.h"

gestionvariableWindow::gestionvariableWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gestionvariableWindow),
    varMan(&VariablesManager::donnerInstance()),
    selectedIdentifierName("")
{
    ui->setupUi(this);
    setWindowTitle("Gestion des variables");

    ui->vueVariable->horizontalHeader()->setStretchLastSection(true); //Permet d'étirer la vue au maximum de la taille
    ui->vueVariable->setRowCount(varMan->getNbVar());  //initialise le nombre de ligne de la vue
    ui->vueVariable->setColumnCount(2);  // Idem avec les colonnes

    connect(ui->button_refresh,SIGNAL(clicked(bool)),this,SLOT(regenerateVueVariable()));
    connect(ui->button_quit,SIGNAL(clicked(bool)),MainWindow::getInstanceMainWindow(),SLOT(closeVariableWindow()));
    connect(ui->vueVariable,SIGNAL(cellChanged(int,int)),this,SLOT(modifierVariable(int,int)));
    connect(ui->vueVariable,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(saveIdentifierName(int,int)));
    regenerateVueVariable();
}

gestionvariableWindow::~gestionvariableWindow()
{
    delete ui;
}

void gestionvariableWindow::refreshVueVariable(){
    //Rafraichir l'état de la vue des variables

    for(int i=0; i< ui->vueVariable->rowCount();i++){
        ui->vueVariable->item(i,0)->setText("");
        ui->vueVariable->item(i,1)->setText("");
    }
    unsigned int nb = 0;

    for(QMap<QString,Litterale*>::iterator it=varMan->getVariablesBegin() ; it!=varMan->getVariablesEnd() && nb!=varMan->getNbVar();++it){
       if(!estdeType<Programme>(it.value())){
        ++nb;
        ui->vueVariable->item(nb-1,0)->setText(it.key());
        ui->vueVariable->item(nb-1,1)->setText(it.value()->toString());
    }
    }
}

void gestionvariableWindow::regenerateVueVariable(){

    disconnect(ui->vueVariable,SIGNAL(cellChanged(int,int)),this,SLOT(modifierVariable(int,int)));
    for(int i=0;ui->vueVariable->rowCount()>i;i++)
        delete ui->vueVariable->item(i,0);


    ui->vueVariable->setRowCount(varMan->getNbVar());
    for(unsigned int i=0;varMan->getNbVar()>i;i++){
        ui->vueVariable->setItem(i,0,new QTableWidgetItem(""));
        ui->vueVariable->setItem(i,1,new QTableWidgetItem(""));
    }

    refreshVueVariable();
    connect(ui->vueVariable,SIGNAL(cellChanged(int,int)),this,SLOT(modifierVariable(int,int)));
}

void gestionvariableWindow::modifierVariable(int i, int j){
    if(j==0){
        Litterale* tmp = varMan->getVariable(selectedIdentifierName);
        QString newIdentifier = ui->vueVariable->item(i,0)->text();
        if(Atome::isValidAtomeName(newIdentifier)){
            varMan->supprimer(selectedIdentifierName);
            varMan->enregistrer(newIdentifier,tmp);
        }
    }
    else if(j==1){
        QString _nomVariable = ui->vueVariable->item(i,0)->text();
        QString _valueVariable = ui->vueVariable->item(i,1)->text();
        Litterale* l = nullptr;
        try{
        l = LitteraleFactory::donnerInstance().creerInfixLitterale(_valueVariable);
        }
        catch(LitteraleException& e){
            ui->message->setText("Nombre non valide");
            delete l;
            return;
        }
        if(l){
        varMan->supprimer(_nomVariable);
        varMan->enregistrer(_nomVariable,l);
        }
    }
    regenerateVueVariable();
}

void gestionvariableWindow::saveIdentifierName(int i,int j){
    if(j==0)
        selectedIdentifierName=ui->vueVariable->item(i,j)->text();
}

void gestionvariableWindow::on_button_add_clicked()
{
    QString id = ui->add_id->text();
    Litterale* l = nullptr;
    if(!Atome::isValidAtomeName(id)){
        ui->message->setText("Nom non valide");
        return;
    }
    try{
        varMan->getVariable(id);
        ui->message->setText("Nom déjà pris");
        return;
    }
    catch(LitteraleException& e){

    }
    try{
    l = LitteraleFactory::donnerInstance().creerInfixLitterale(ui->add_value->text());
    }
    catch(LitteraleException& e){
        ui->message->setText("Nombre non valide");
        delete l;
        return;
    }
    if(l){
        varMan->enregistrer(id,l);
        ui->message->setText("Ajout réussi");
        regenerateVueVariable();
        return;
    }
    ui->message->setText("Nombre non valide");
    return;
}
