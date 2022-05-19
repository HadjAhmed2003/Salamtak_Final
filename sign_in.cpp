#include "sign_in.h"
#include "ui_sign_in.h"
#include <QSqlDatabase>
#include <QSqlQuery>
sign_in::sign_in(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sign_in)
{
    ui->setupUi(this);
}

sign_in::~sign_in()
{
    delete ui;
}

void sign_in::connect_db(){
    db.setConnectOptions();
    db.setDatabaseName("Driver={SQL Server};Server=.\\SQLEXPRESS;Database=salamtak;Trusted_Connection=Yes;");
    db.open();
}

void sign_in::on_sign_in_2_clicked()
{
    email = ui->email->text();
    password = ui->password->text();
    if((email == "")||(password == "")){
        ui->validation->setText("Enter all the necessary infromation");
    }else{
        connect_db();
        query.exec(QString("SELECT CASE WHEN EXISTS (SELECT * FROM patient_info WHERE email='%1')THEN 'TRUE' ELSE 'FALSE' END").arg(email));
        query.next();
        email_exists = query.value(0).toBool();
        if(email_exists){
            query.exec(QString("SELECT password_patient FROM patient_info WHERE email='%1'").arg(email));
            query.next();
            temp_password = query.value(0).toString();
            if(temp_password==password){
                db.close();
                service_window = new service_choice();
                this->hide();
                service_window->show();
                return;
            }else{
                ui->validation->setText("Incorrect password");
                db.close();
                return;
            }
        }else{
            ui->validation->setText("Inexistant email address");
            db.close();
            return;
        }
    }
}

