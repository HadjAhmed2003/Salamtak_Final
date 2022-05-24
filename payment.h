#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDialog>
#include "finance.h"
#include <QSqlDatabase>
#include <QSqlQuery>
namespace Ui {
class payment;
}

class payment : public QDialog
{
    Q_OBJECT

public:
    explicit payment(QString full_name = "", int price = 0, QString date = "", QString national_id = "", QWidget *parent = nullptr );
    ~payment();

private slots:
    void on_money_clicked();

    void on_payment_method_currentTextChanged(const QString &arg1);

    void on_confirm_card_clicked();

    void on_confirm_payment_clicked();

private:
    Ui::payment *ui;
    finance* finance_window;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QSqlQuery query;
    void connect_db();
    int user_balance;
    int doctor_price;
    QString user_card_number;
    bool already_paid = false;
};

#endif // PAYMENT_H
