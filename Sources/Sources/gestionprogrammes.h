#ifndef GESTIONPROGRAMMES_H
#define GESTIONPROGRAMMES_H

#include <QWidget>

namespace Ui {
class gestionprogrammes;
}

class gestionprogrammes : public QWidget
{
    Q_OBJECT

public:
    explicit gestionprogrammes(QWidget *parent = 0);
    ~gestionprogrammes();

private:
    Ui::gestionprogrammes *ui;
};

#endif // GESTIONPROGRAMMES_H
