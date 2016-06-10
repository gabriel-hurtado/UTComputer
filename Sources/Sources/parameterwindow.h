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
    explicit ParameterWindow(QWidget *parent = 0);
    ~ParameterWindow();
signals :
    void sendHideKeyboard(int);
    void sendMuteError(int);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_button_validate_clicked();

    void on_button_variable_remove_clicked();

private:
    Ui::ParameterWindow *ui;
};

#endif // PARAMETERWINDOW_H
