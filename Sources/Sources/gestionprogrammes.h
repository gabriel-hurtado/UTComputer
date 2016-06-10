#ifndef GESTIONPROGRAMMES_H
#define GESTIONPROGRAMMES_H

#include <QWidget>

class VariablesManager;

namespace Ui {
class gestionprogrammes;
}

class gestionprogrammes : public QWidget
{
    Q_OBJECT

public:
    explicit gestionprogrammes(QWidget *parent = 0);
    ~gestionprogrammes();
    VariablesManager& varMan;

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::gestionprogrammes *ui;

public slots:
    void refreshComboBox();

private slots:
    void on_button_save_clicked();
    void on_pushButton_clicked();
    void on_combo_programmes_currentTextChanged(const QString &arg1);
    void on_button_new_clicked();
};

#endif // GESTIONPROGRAMMES_H
