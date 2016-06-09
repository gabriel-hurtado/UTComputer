#include "gestionprogrammes.h"
#include "ui_gestionprogrammes.h"

gestionprogrammes::gestionprogrammes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gestionprogrammes)
{
    ui->setupUi(this);
}

gestionprogrammes::~gestionprogrammes()
{
    delete ui;
}
