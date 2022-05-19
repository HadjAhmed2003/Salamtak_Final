#ifndef PATIENT_SIGN_UP_H
#define PATIENT_SIGN_UP_H
#include "sign_in.h"
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QCheckBox>
namespace Ui {
class patient_sign_up;
}

class patient_sign_up : public QWidget
{
    Q_OBJECT

public:
    explicit patient_sign_up(QWidget *parent = nullptr);
    ~patient_sign_up();

private slots:
    void connect_db();

    void on_yes_clicked();

    void on_no_clicked();

    void on_sign_up_clicked();

private:
    Ui::patient_sign_up *ui;
    QString first_name, last_name, email,password_patient, phone_number,national_id, date_of_birth, gender, insurance = "00000";
    bool insured;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QSqlQuery query;
    QVector<QString> patient_diseases;
    QCheckBox* disease_check_box[322];
    sign_in *sign_in_window;
};

#endif // PATIENT_SIGN_UP_H
