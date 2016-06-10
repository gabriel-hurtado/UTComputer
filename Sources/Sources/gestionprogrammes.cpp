#include "gestionprogrammes.h"
#include "ui_gestionprogrammes.h"
#include "variable.h"
#include "litterales.h"
#include "mainwindow.h"
#include "litteralefactory.h"

gestionprogrammes::gestionprogrammes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gestionprogrammes),
    varMan(VariablesManager::donnerInstance())
{
    ui->setupUi(this);
    refreshComboBox();

}

gestionprogrammes::~gestionprogrammes()
{
    delete ui;
}

void gestionprogrammes::refreshComboBox(){
    ui->combo_programmes->clear();
    QMap<QString,Litterale* >::const_iterator it = varMan.getVariablesBegin();
    for(;it!=varMan.getVariablesEnd();it++){
        if(estdeType<Programme>(it.value()))
            ui->combo_programmes->addItem(" "+it.key());
    }
}

void gestionprogrammes::closeEvent(QCloseEvent *event){
    MainWindow* main = MainWindow::getInstanceMainWindow();
    main->closeProgramWindow();
    event->ignore();
}

void gestionprogrammes::on_button_save_clicked(){
    Litterale* l = LitteraleFactory::donnerInstance().creerRPNLitterale(ui->text_program->toPlainText());
    if(estdeType<Programme>(l)){
        QString c = ui->combo_programmes->currentText();
        c.remove(0,1);
        varMan.supprimer(c);
        varMan.enregistrer(c,l);
    }

}

void gestionprogrammes::on_pushButton_clicked()
{
    QString c = ui->combo_programmes->currentText();
    c.remove(0,1);
    varMan.supprimer(c);
    refreshComboBox();
    ui->combo_programmes->clear();
}

void gestionprogrammes::on_combo_programmes_currentTextChanged(const QString &arg1)
{
    QString c = ui->combo_programmes->currentText();
    if(c!=""){
        c.remove(0,1);
        ui->text_program->setText(varMan.getVariable(c)->toString());
}   }

void gestionprogrammes::on_button_new_clicked()
{
    QString Name = ui->nom->text();
    if(Atome::isValidAtomeName(Name)){
        varMan.enregistrer(Name,LitteraleFactory::donnerInstance().creerRPNLitterale("[]"));
        refreshComboBox();
    }
}
