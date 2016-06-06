#include "gestionvariablewindow.h"
#include "ui_gestionvariablewindow.h"

gestionvariableWindow::gestionvariableWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gestionvariableWindow)
{
    ui->setupUi(this);
}

gestionvariableWindow::~gestionvariableWindow()
{
    delete ui;
}
