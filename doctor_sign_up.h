#ifndef DOCTOR_SIGN_UP_H
#define DOCTOR_SIGN_UP_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QCheckBox>
#include "sign_in.h"
namespace Ui {
class doctor_sign_up;
}

class doctor_sign_up : public QDialog
{
    Q_OBJECT

public:
    explicit doctor_sign_up(QWidget *parent = nullptr);
    ~doctor_sign_up();

private slots:
    void connect_db();
    void on_submit_clicked();

private:
    Ui::doctor_sign_up *ui;
    QString first_name, last_name, email,password_doctor, phone_number,national_id, gender, specialization, price_str;
    int price;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QSqlQuery query;
    QCheckBox* days_check_box[7];
    sign_in* sign_in_window;

};

#endif // DOCTOR_SIGN_UP_H
