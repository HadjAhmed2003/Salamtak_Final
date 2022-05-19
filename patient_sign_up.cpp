#include "patient_sign_up.h"
#include "ui_patient_sign_up.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QScrollArea>
#include <QCheckBox>
#include <QDebug>
patient_sign_up::patient_sign_up(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::patient_sign_up)
{
    ui->setupUi(this);
    ui->insurance_number->hide();
    ui->insurance_label->hide();
    connect_db();
//    parent->setGeometry(QRect(0,0,700,700));
    QScrollArea* scrollArea = new QScrollArea(ui->widget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setGeometry(QRect(0,0, 450, 150));
    QWidget* checkboxes = new QWidget(scrollArea);
    QVBoxLayout* layout = new QVBoxLayout(checkboxes);
//    layout->setGeometry(QRect(0,0, 100, 100));
    query.exec("SELECT * FROM diseases_dataset");
    for (int i = 0; i < 322; ++i)
    {
       query.next();
       disease_check_box[i] = new QCheckBox(checkboxes);
       disease_check_box[i] ->setText(query.value(0).toString());
       layout->addWidget(disease_check_box[i]);
      }
     scrollArea->setWidget(checkboxes);
}

patient_sign_up::~patient_sign_up()
{
    delete ui;
}

void patient_sign_up::connect_db(){
    db.setConnectOptions();
    db.setDatabaseName("Driver={SQL Server};Server=.\\SQLEXPRESS;Database=salamtak;Trusted_Connection=Yes;");
    db.open();
}


void patient_sign_up::on_yes_clicked()
{
    ui->insurance_label->show();
    ui->insurance_number->show();

}


void patient_sign_up::on_no_clicked()
{
    ui->insurance_number->hide();
    ui->insurance_label->hide();
}


void patient_sign_up::on_sign_up_clicked()
{
    first_name = ui->first_name->text();
    last_name = ui->last_name->text();
    email = ui->email->text();
    date_of_birth = ui->date_of_birth->text();
    password_patient = ui->password->text();
    national_id = ui->national_id->text();
    phone_number = ui->phone_number->text(); 
    for (int i = 0; i < 322; ++i)
    {
        if(disease_check_box[i]->isChecked()){
            patient_diseases.push_back(disease_check_box[i]->text());
        }
    }
    if((ui->yes->isChecked())||(ui->no->isChecked())){
       if(ui->yes->isChecked()){
           insured = true;
           insurance = ui->insurance_number->text();
           if(insurance == ""){
               ui->validation->setText("Please fill out the whole form");
               return;
           }
       }else{
           insured = false;
       }
    }else{
        ui->validation->setText("Please fill out the whole form");
        return;
    }
    if((ui->female->isChecked())||(ui->male->isChecked())){
        if(ui->female->isChecked()){
            gender = ui->female->text();
        }else{
            gender = ui->male->text();
        }
    }else{
        ui->validation->setText("Please fill out the whole form");
        return;
    }
    if((first_name=="")||(last_name=="")||(email=="")||(date_of_birth=="")||(password_patient=="")||(national_id=="")||(phone_number=="")){
        ui->validation->setText("Please fill out the whole form");
        return;
    }else{
        query.exec(QString("SELECT national_id FROM patient_info WHERE national_id='%1'").arg(national_id));
        query.next();
        QString temp_national_id = query.value(0).toString();
        query.exec(QString("SELECT email FROM patient_info WHERE email='%1'").arg(email));
        query.next();
        QString temp_email = query.value(0).toString();
        ui->validation->setText(temp_email);
        if((temp_national_id==national_id)&&(temp_email==email)){
            ui->validation->setText("National ID and email already exist in the system");
            return;
        }else if(temp_national_id==national_id){
            ui->validation->setText("National ID already exists in the system");
            return;
        }else if(temp_email==email){
            ui->validation->setText("Email address already exists in the system");
            return;
        }else{
            if(ui->yes->isChecked()){
                QString temp_insurance;
                if(insurance==""){
                    ui->validation->setText("Please fill out the whole form");
                    return;
                }else{
                    query.exec(QString("SELECT insurance_number FROM insurance WHERE national_id='%1'").arg(national_id));
                    query.next();
                    temp_insurance = query.value(0).toString();
                }
                if(insurance == temp_insurance){
                    query.exec(QString("INSERT INTO patient_info VALUES('%1','%2','%3','%4','%5','%6','%7','%8','%9')").arg(national_id).arg(first_name).arg(last_name).arg(gender).arg(email).arg(password_patient).arg(phone_number).arg(date_of_birth).arg(insured));
                    if(patient_diseases.size()>0){
                        for(int i=0; i<patient_diseases.size(); i++){
                            query.exec(QString("INSERT INTO patient_diseases VALUES('%1', '%2')").arg(national_id).arg(patient_diseases[i]));
                        }
                    db.close();
                    sign_in_window = new sign_in();
                    sign_in_window->patient = true;
                    this->hide();
                    sign_in_window->show();
                    return;

                }else{
                    ui->validation->setText("Invalid insurance number");
                    return;
                }
            }
            }else{
                query.exec(QString("INSERT INTO patient_info VALUES('%1','%2','%3','%4','%5','%6','%7','%8','%9')").arg(national_id).arg(first_name).arg(last_name).arg(gender).arg(email).arg(password_patient).arg(phone_number).arg(date_of_birth).arg(insured));
                if(patient_diseases.size()>0){
                    for(int i=0; i<patient_diseases.size(); i++){
                        query.exec(QString("INSERT INTO patient_diseases VALUES('%1', '%2')").arg(national_id).arg(patient_diseases[i]));
                    }
                    db.close();
                    sign_in_window = new sign_in();
                    sign_in_window->patient = true;
                    this->hide();
                    sign_in_window->show();
                    return;
                }else{
                    db.close();
                    sign_in_window = new sign_in();
                    sign_in_window->patient = true;
                    this->hide();
                    sign_in_window->show();
                    return;
                }
            }
        }
    }
}
