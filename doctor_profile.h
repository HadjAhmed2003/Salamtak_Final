#ifndef DOCTOR_PROFILE_H
#define DOCTOR_PROFILE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QCheckBox>
namespace Ui {
class doctor_profile;
}

class doctor_profile : public QDialog
{
    Q_OBJECT

public:
    explicit doctor_profile(QString id_par = "", QWidget *parent = nullptr);
    ~doctor_profile();

private slots:
    void on_cancel_visits_clicked();

private:
    Ui::doctor_profile *ui;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QSqlQuery query;
    void connect_db();
    QVector<QString> visits;
    //QCheckBox* visits_check_boxes[100];
    QVector<QCheckBox*> visits_check_boxes;
    QString id, patient_name, diseases, patient_id;
};

#endif // DOCTOR_PROFILE_H
