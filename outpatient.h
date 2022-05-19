#ifndef OUTPATIENT_H
#define OUTPATIENT_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QWidget>
#include <QVector>
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

    void on_back_clicked();

    void on_submit_spe_clicked();

    void on_reset_clicked();

    void on_submit_date_clicked();

    void on_submit_booking_clicked();

private:
    Ui::outpatient *ui;
    QString speciality, doctor, date, patient;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QSqlQuery query;
    QVector<QString> doctors_ids;
};

#endif // OUTPATIENT_H
