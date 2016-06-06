#ifndef GESTIONVARIABLEWINDOW_H
#define GESTIONVARIABLEWINDOW_H

#include <QWidget>

namespace Ui {
class gestionvariableWindow;
}

class gestionvariableWindow : public QWidget
{
    Q_OBJECT

public:
    explicit gestionvariableWindow(QWidget *parent = 0);
    ~gestionvariableWindow();

private:
    Ui::gestionvariableWindow *ui;
};

#endif // GESTIONVARIABLEWINDOW_H
