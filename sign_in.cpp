#include "sign_in.h"
#include "ui_sign_in.h"
#include <QSqlDatabase>
#include <QSqlQuery>
sign_in::sign_in(QString type_par, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sign_in)
{
    ui->setupUi(this);
    type = type_par;
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
        query.exec(QString("SELECT CASE WHEN EXISTS (SELECT * FROM %1_info WHERE email='%2')THEN 'TRUE' ELSE 'FALSE' END").arg(type).arg(email));
        query.next();
        email_exists = query.value(0).toBool();
        if(email_exists){
            if(type == "doctors")
                query.exec(QString("SELECT password_doctor FROM doctors_info WHERE email='%1'").arg(email));
            if(type == "patient")
                query.exec(QString("SELECT password_patient FROM patient_info WHERE email='%1'").arg(email));
            query.next();
            temp_password = query.value(0).toString();
            if(temp_password==password){
                qDebug()<<"success"; //the flow splits here according to each type patient->booking window; doctor->profile
                if(type == "patient"){
                    service_window = new service_choice();
                    this->hide();
                    service_window->patient_email = ui->email->text();
                    service_window->show();
                    db.close();
                    return;
                }
                if(type == "doctors"){
                    query.exec(QString("SELECT national_id FROM doctors_info WHERE email='%1'").arg(email));
                    query.next();
                    QString id = query.value(0).toString();
                    //some code to open the profile window
                    qDebug()<<"id of the doctor to be passed to the profile: "<<id;
                    doctor_profile_window = new doctor_profile(id);
                    this->hide();
                    doctor_profile_window->show();
                    db.close();
                    return;
                }

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

