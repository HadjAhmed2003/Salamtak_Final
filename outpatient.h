#ifndef OUTPATIENT_H
#define OUTPATIENT_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QWidget>
#include "payment.h"
#include <QVector>
#include <QSqlQueryModel>
namespace Ui {
class outpatient;
}

class outpatient : public QWidget
{
    Q_OBJECT

public:
    explicit outpatient(QWidget *parent = nullptr);
    ~outpatient();
    QString email;

private slots:
    void connect_db();

    void show_visits();

    void on_submit_spe_clicked();

    void on_reset_clicked();

    void on_submit_date_clicked();

    void on_submit_booking_clicked();

private:
    Ui::outpatient *ui;
    QString speciality, doctor_id, date, patient_id, department, doctor_name;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QSqlQuery query;
    payment* pay_window;
    QString firstname = "", lastname;
    int price;
    QVector<QString> doctors_ids;
    QSqlQueryModel* model;
};

#endif // OUTPATIENT_H
