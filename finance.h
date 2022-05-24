#ifndef FINANCE_H
#define FINANCE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
namespace Ui {
class finance;
}

class finance : public QDialog
{
    Q_OBJECT

public:
    explicit finance(QWidget *parent = nullptr);
    ~finance();

private slots:

    void on_submit_create_clicked();

    void on_sumbit_recharge_clicked();

    void on_recharge_clicked();

private:
    Ui::finance *ui;
    QString id, card;
    int balance_create, amount;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    QSqlQuery query;
    void connect_db();
};

#endif // FINANCE_H
