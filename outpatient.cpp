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
    connect_db();
    query.exec(QString("select national_id from patient_info where email='%1'").arg(email));
    query.next();
    patient_id = query.value(0).toString();
    query.prepare(QString("select Department, Doctor_name, TheDate from visits where (patient_id='%1' and isCurrent = '1')").arg(patient_id));
    query.exec();
    model = new QSqlQueryModel();
    model->setQuery(query);
    ui->tableView->setModel(model);

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
    doctor_id= "";
    date="";
}





void outpatient::on_submit_date_clicked()
{
    QString id, firstname, lastname;
    int price;
    date = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    query.exec(QString("select national_id from doctor_working_days where (TheDate='%1' AND available = '1')").arg(date));
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
}


void outpatient::on_submit_booking_clicked()
{
    doctor_id = doctors_ids[ui->doctors->currentIndex()];
    query.exec(QString("select national_id from patient_info where email='%1'").arg(email));
    query.next();
    patient_id = query.value(0).toString();
    query.exec(QString("select first_name from doctors_info where national_id='%1'").arg(doctor_id));
    query.next();
    doctor_name = query.value(0).toString();
    query.exec(QString("insert into visits values('%1', '%2', '%3', 'true', '%4', '%5')").arg(doctor_id).arg(patient_id).arg(date).arg(speciality).arg(doctor_name));
    query.exec(QString("UPDATE doctor_working_days SET available ='0' WHERE TheDate = '%1'").arg(date));
    on_reset_clicked();
    query.prepare(QString("select Department, Doctor_name, TheDate from visits where (patient_id='%1' and isCurrent = '1')").arg(patient_id));
    query.exec();
    model->setQuery(query);
    ui->tableView->setModel(model);
}

