#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "sign_in.h"
#include "patient_sign_up.h"
#include "doctor_sign_up.h"
#include <QMainWindow>
#include <QSqlDatabase>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sign_up_clicked();

    void on_sign_in_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    patient_sign_up *patient_window;
    sign_in *sign_in_window;
    doctor_sign_up * doctor_signup_window;

};
#endif // MAINWINDOW_H
