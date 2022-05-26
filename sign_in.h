#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "service_choice.h"
#include "doctor_profile.h"
namespace Ui {
class sign_in;
}

class sign_in : public QWidget
{
    Q_OBJECT

public:
    bool patient, doctor, receptionist;
    explicit sign_in(QString type_par = "", QWidget *parent = nullptr);
    ~sign_in();

private slots:
    void connect_db();
    void on_sign_in_2_clicked();

private:
    Ui::sign_in *ui; 
    QString email, password, temp_password, type;
    bool email_exists;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QSqlQuery query;
    service_choice* service_window;
    doctor_profile* doctor_profile_window;
};

#endif // SIGN_IN_H
