#include "parameterwindow.h"
#include "ui_parameterwindow.h"
#include "mainwindow.h"

ParameterWindow::ParameterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterWindow)
{
    ui->setupUi(this);
    setWindowTitle("Gestion des paramètres");
    connect(ui->button_close,SIGNAL(clicked(bool)),MainWindow::getInstanceMainWindow(),SLOT(closeParameterWindow()));

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
    bool ok;
    QString tmp = ui->nb_item_affiche->text();
    unsigned int i = tmp.toInt(&ok);
    if(ok){
        Pile::donnerInstance().setNbToAffiche(i);
    }
}
