#include "finance.h"
#include "ui_finance.h"
#include <QIntValidator>
finance::finance(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::finance)
{
    ui->setupUi(this);
    ui->credit_create->setValidator( new QIntValidator(0, 10000000, this) );
    ui->charge->setValidator( new QIntValidator(0, 10000000, this) );
    connect_db();
    ui->validation_create->hide();
    ui->validation_recharge->hide();
    ui->validation_wallet->hide();
}

void finance::connect_db(){
    db.setConnectOptions();
    db.setDatabaseName("Driver={SQL Server};Server=.\\SQLEXPRESS;Database=salamtak;Trusted_Connection=Yes;");
    if(db.open())
        qDebug()<<"data base opened successfully";
}

finance::~finance()
{
    delete ui;
}


void finance::on_submit_create_clicked()
{
    id = ui->id->text();
    card = ui->credit_create->text();
    balance_create = (ui->charge->text()).toInt();
    if(ui->credit_create->text() == "" || ui->charge->text() == "" || ui->id->text() == ""){
        ui->validation_create->show();
        ui->validation_create->setText("empty fields have been deteced");
        return;
    }else{
        query.exec(QString("SELECT CASE WHEN EXISTS (SELECT national_id FROM patient_info WHERE national_id = '%1')THEN 'TRUE' ELSE 'FALSE' END;").arg(id));
        query.next();
        bool id_exists = query.value(0).toBool();
        if(id_exists){
            ui->validation_create->show();
            ui->validation_create->setText("id exists");
            query.exec(QString("SELECT first_name from patient_info WHERE national_id = '%1'").arg(id));
            query.next();
            ui->name->setText(query.value(0).toString());
        }else{
            ui->validation_create->show();
            ui->validation_create->setText("wrong id");
            return;
        }
        query.exec(QString("SELECT CASE WHEN EXISTS (SELECT credit_card FROM credit_cards WHERE credit_card = '%1')THEN 'TRUE' ELSE 'FALSE' END").arg(card));
        query.next();
        bool card_already_exist  = query.value(0).toBool();
        if(card_already_exist)
        {
            ui->validation_create->show();
            ui->validation_create->setText("card already exists try another card number");

        }else{
            query.exec(QString("INSERT INTO credit_cards (id, credit_card, balance) VALUES ('%1', '%2', %3);").arg(id).arg(card).arg(QString::number(balance_create)));
            ui->validation_create->show();
            ui->validation_create->setText("successful");
        }

    }

}


void finance::on_sumbit_recharge_clicked()
{
    card = ui->credit_recharge->text();
    amount = (ui->amount->text()).toInt();
    if(ui->credit_recharge->text() == "" || ui->amount->text() == ""){
        ui->validation_recharge->show();
        ui->validation_recharge->setText("no empy fields are allowed");
        return;
    }else{
        query.exec(QString("SELECT CASE WHEN EXISTS (SELECT credit_card FROM credit_cards WHERE credit_card = '%1')THEN 'TRUE' ELSE 'FALSE' END;").arg(card));
        query.next();
        bool card_already_exist  = query.value(0).toBool();
        if(card_already_exist){
            int existent_balance;
            query.exec(QString("SELECT balance FROM credit_cards WHERE credit_card = '%1'").arg(card));
            query.next();
            existent_balance = query.value(0).toInt();
            qDebug()<<existent_balance;
            query.exec(QString("UPDATE credit_cards SET balance = %1 WHERE credit_card = '%2';").arg(amount + existent_balance).arg(card));
            ui->validation_recharge->show();
            ui->validation_recharge->setText("success");
        }else{
            ui->validation_recharge->show();
            ui->validation_recharge->setText("the card number you entered is wrong");
        }
    }
}


void finance::on_recharge_clicked()
{
    amount = (ui->amount_wallet->text()).toInt();
    id = ui->id_wallet->text();
    if(ui->amount_wallet->text() == "" || ui->id_wallet->text() == ""){
        ui->validation_wallet->show();
        ui->validation_wallet->setText("no empy fields are allowed");
        return;
    }else{
        query.exec(QString("SELECT CASE WHEN EXISTS (SELECT national_id FROM patient_info WHERE national_id = '%1')THEN 'TRUE' ELSE 'FALSE' END;").arg(id));
        query.next();
        bool id_exists = query.value(0).toBool();
        if(!id_exists){
            ui->validation_wallet->show();
            ui->validation_wallet->setText("wrong id");
            return;
        }
        int existent_balance;
        query.exec(QString("SELECT wallet FROM patient_info WHERE national_id = '%1'").arg(id));
        query.next();
        existent_balance = query.value(0).toInt();
        query.exec(QString("UPDATE patient_info SET wallet = %1 WHERE national_id = '%2'").arg(existent_balance + amount).arg(id));
        ui->validation_wallet->show();
        ui->validation_wallet->setText("success");
    }

}

