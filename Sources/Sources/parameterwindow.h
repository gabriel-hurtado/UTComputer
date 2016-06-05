#ifndef PARAMETERWINDOW_H
#define PARAMETERWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class ParameterWindow;
}

class ParameterWindow : public QWidget
{
    Q_OBJECT

public:
    friend class MainWindow;
    explicit ParameterWindow(QWidget *parent = 0);
    ~ParameterWindow();

private slots:
    void on_button_validate_clicked();

private:
    Ui::ParameterWindow *ui;
};

#endif // PARAMETERWINDOW_H
