#include "outpatient.h"
#include "ui_outpatient.h"
#include <QVector>
#include <QDebug>
outpatient::outpatient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::outpatient)
{
    ui->setupUi(this);
    ui->calendarWidget->hide();
    ui->doctors->hide();
    ui->submit_booking->hide();
    ui->submit_date->hide();
    ui->submit_booking->hide();
    ui->doctor_label->hide();
}

outpatient::~outpatient()
{
    delete ui;
}
void outpatient::connect_db(){
    db.setConnectOptions();
    db.setDatabaseName("Driver={SQL Server};Server=.\\SQLEXPRESS;Database=salamtak;Trusted_Connection=Yes;");
    db.open();
}

void outpatient::on_back_clicked()
{

}


void outpatient::on_submit_spe_clicked()
{
    speciality = ui->specialities->currentText();
    ui->specialities->setDisabled(true);
    ui->submit_spe->setDisabled(true);
    ui->calendarWidget->show();
    ui->calendarWidget->setEnabled(true);
    ui->submit_date->show();
    ui->submit_date->setEnabled(true);
}


void outpatient::on_reset_clicked()
{
    ui->specialities->setEnabled(true);
    ui->submit_spe->setEnabled(true);
    ui->calendarWidget->hide();
    ui->calendarWidget->setEnabled(true);
    ui->doctors->hide();
    ui->doctors->setEnabled(true);
    ui->submit_booking->hide();
    ui->submit_booking->setEnabled(true);
    ui->submit_date->hide();
    ui->submit_date->setEnabled(true);
    ui->doctor_label->hide();
    speciality="";
    doctor= "";
    date="";
}





void outpatient::on_submit_date_clicked()
{
    connect_db();
    QString id, firstname, lastname;
    int price;
    date = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    QVector<QString> doctors_ids;
    query.exec(QString("select national_id from doctor_working_days where TheDate='%1'").arg(date));
    qDebug()<<query.lastQuery();
    while(query.next()){
        id = query.value(0).toString();
        doctors_ids.push_back(id);
    }
    for(int j=0; j<doctors_ids.size();j++){
        qDebug()<<doctors_ids[j];
    }
    for(int i=0; i<doctors_ids.size();i++){
        query.exec(QString("select first_name, last_name, price from doctors_info where (national_id='%1' AND specialization = '%2')").arg(doctors_ids[i]).arg(speciality));
        query.next();
        firstname = query.value(0).toString();
        lastname = query.value(1).toString();
        price = query.value(2).toInt();
        ui->doctors->addItem(QString("%1 %2 %3").arg(firstname).arg(lastname).arg(price));
    }
    ui->doctors->show();
    ui->submit_booking->show();
    ui->calendarWidget->setDisabled(true);
    ui->submit_date->setDisabled(true);
    db.close();
}

