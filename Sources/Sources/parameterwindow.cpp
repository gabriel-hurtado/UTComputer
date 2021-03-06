#include "parameterwindow.h"
#include "ui_parameterwindow.h"
#include "mainwindow.h"
#include "pile.h"
#include "variable.h"

ParameterWindow::ParameterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterWindow)
{
    ui->setupUi(this);
    setWindowTitle("Gestion des paramètres");
    if(!MainWindow::keyboard){
        ui->check_clavier->setChecked(0);
    }
    if(!MainWindow::sound){
        ui->check_bip->setChecked(0);
    }
    connect(ui->button_close,SIGNAL(clicked(bool)),MainWindow::getInstanceMainWindow(),SLOT(closeParameterWindow()));
    connect(this,SIGNAL(sendHideKeyboard(int)),MainWindow::getInstanceMainWindow(),SLOT(hideKeyboard(int)));
    connect(this,SIGNAL(sendMuteError(int)),MainWindow::getInstanceMainWindow(),SLOT(muteError(int)));

    /*
        Affichage du nombre d'items dispo
    */

    QString tmp;
    tmp.setNum(Pile::donnerInstance().getNbToAffiche());
    ui->nb_item_affiche->setText(tmp);
}

ParameterWindow::~ParameterWindow()
{
    delete ui;
}

void ParameterWindow::on_button_validate_clicked()
{
    /*
        Gestion du nombre de lignes a afficher
    */
    QString tmp = ui->nb_item_affiche->text();
    bool ok;
    int i = tmp.toInt(&ok);
    if(ok && Pile::donnerInstance().getNbToAffiche()!=static_cast<unsigned int>(i) && i>=0){
            Pile::donnerInstance().setNbToAffiche(i);
    }

    /*
        Gestion du clavier cliquable
    */
   if(ui->check_clavier->isChecked()){
       sendHideKeyboard(0);
   }
   else
       sendHideKeyboard(1);

   /*
        Gestion du son
    */
   if(ui->check_bip->isChecked())
       sendMuteError(0);
   else
       sendMuteError(1);
}

void ParameterWindow::on_button_variable_remove_clicked()
{
    VariablesManager::clearVariables();
}

void ParameterWindow::closeEvent(QCloseEvent *event){
    MainWindow* main = MainWindow::getInstanceMainWindow();
    main->closeParameterWindow();
    event->ignore();
}
