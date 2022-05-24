#include "payment.h"
#include "ui_payment.h"

payment::payment(QString full_name, int price, QString date, QString national_id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::payment)
{
    ui->setupUi(this);
    connect_db();
    ui->date->setText(date);
    ui->price->setText(QString::number(price));
    doctor_price = price;
    ui->name->setText(full_name);
    ui->payment_method->addItem("cash");
    ui->payment_method->addItem("card");
    ui->payment_method->addItem("insured");
    ui->personal_info->hide();
    ui->card->hide();
    ui->card_labe->hide();
    ui->confirm_card->hide();
}

void payment::connect_db(){
    db.setConnectOptions();
    db.setDatabaseName("Driver={SQL Server};Server=.\\SQLEXPRESS;Database=salamtak;Trusted_Connection=Yes;");
    if(db.open())
        qDebug()<<"data base opened successfully";
}

payment::~payment()
{
    delete ui;
}

void payment::on_money_clicked()
{
    finance_window = new finance();
    finance_window->show();
}


void payment::on_payment_method_currentTextChanged(const QString &arg1)
{
    if(arg1 == "card"){
        qDebug()<<"credit card yay!";
        ui->card->show();
        ui->card_labe->show();
        ui->confirm_card->show();
        ui->confirm_payment->show();
        ui->card_validation->setText("");
    }else if (arg1 == "cash"){
        ui->card->hide();
        ui->card_labe->hide();
        ui->confirm_card->hide();
        ui->confirm_payment->hide();
        ui->card_validation->setText("you will pay at the receptionist once you arrive");
    }else{
        ui->card->hide();
        ui->card_labe->hide();
        ui->confirm_card->hide();
        ui->confirm_payment->hide();
        ui->card_validation->setText("you will pay at the receptionist once you arrive");
        ui->card_labe->show();
        ui->card_labe->setText("Insurance number");
        ui->card->show();
        //ui->confirm_card->show();
    }
}


void payment::on_confirm_card_clicked()
{
    QString card_number;
    if(ui->card->text() == ""){
        ui->card_validation->setText("You must enter a number");
        return;
    }else{
        card_number = ui->card->text();
        query.exec(QString("SELECT CASE WHEN EXISTS (SELECT credit_card FROM credit_cards WHERE credit_card = '%1')THEN 'TRUE' ELSE 'FALSE' END").arg(card_number));
        query.next();
        bool card_exists  = query.value(0).toBool();
        if(!card_exists){
            ui->card_validation->setText("Card number is wrong");
            return;
        }else{
            query.exec(QString("SELECT balance FROM credit_cards WHERE credit_card = %1").arg(card_number));
            query.next();
            user_balance = query.value(0).toInt();
            ui->personal_info->show();
            ui->balance->setText(QString::number(user_balance));
            ui->card_number->setText(card_number);
            user_card_number = card_number;
            return;
        }
    }
}


void payment::on_confirm_payment_clicked()
{
    if(user_balance < doctor_price || already_paid == true){
        if(already_paid == true){
            ui->pay_validation->setText("you have already paid");
            return;
        }
        ui->pay_validation->setText("in sufficient balance balance in user accoutn please recharge, or you haven't enetred a credit card");
        return;
    }else{
        query.exec(QString("UPDATE credit_cards SET balance = %1 WHERE credit_card = '%2';").arg(user_balance - doctor_price).arg(user_card_number));
        ui->pay_validation->setText("success, the booking will be added to your profile");
        ui->post_balance->setText(QString::number(user_balance - doctor_price));
        user_balance = user_balance - doctor_price;
        already_paid = true;
    }
}

