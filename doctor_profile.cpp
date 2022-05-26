#include "doctor_profile.h"
#include "ui_doctor_profile.h"
#include <QScrollArea>
#include <QCheckBox>
#include <QDate>

doctor_profile::doctor_profile(QString id_par, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::doctor_profile)
{
    ui->setupUi(this);
    id = id_par;
    connect_db();
    //    parent->setGeometry(QRect(0,0,700,700));
        QScrollArea* scrollArea = new QScrollArea(ui->widget_visits);
        scrollArea->setWidgetResizable(true);
        scrollArea->setGeometry(QRect(0,0, 450, 150));
        QWidget* checkboxes = new QWidget(scrollArea);
        QVBoxLayout* layout = new QVBoxLayout(checkboxes);
    //    layout->setGeometry(QRect(0,0, 100, 100));
        query.exec(QString("SELECT TheDate FROM doctor_working_days WHERE available = '0' AND national_id = '%1'").arg(id));
        qDebug()<<"id: "<<id;
        int i = 0;
        while(query.next()){
            QCheckBox * c = new QCheckBox(checkboxes);
            visits_check_boxes.push_back(c) ;
            qDebug()<<"value of date to be on the checkbos: "<<query.value(0).toString().remove(QChar::Null);
            visits_check_boxes.back()->setText(query.value(0).toString().remove(QChar::Null));
            layout->addWidget(visits_check_boxes.back());
            i++;
        }
         scrollArea->setWidget(checkboxes);
         QString today = QDate::currentDate().toString("yyyy.MM.dd");
         query.exec(QString("SELECT * FROM visits WHERE doctor_id = %1 AND TheDate = '%2';").arg(id).arg(today));//get today's visit
         query.next();
         patient_id = query.value(1).toString();
         QString firstName;
         QString lastName;
         query.exec(QString("SELECT first_name FROM patient_info WHERE national_id = '%1'").arg(patient_id));
         query.next();
         firstName = query.value(0).toString();
         query.exec(QString("SELECT last_name FROM patient_info WHERE national_id = '%1'").arg(patient_id));
         query.next();
         lastName = query.value(0).toString();
         patient_name = firstName + " " + lastName;
         query.exec(QString("select disease_name from patient_diseases Where national_id = '%1'").arg(patient_id));
         while(query.next()){
             diseases = diseases + query.value(0).toString() + " ";
         }
         qDebug()<<"patient name: "<<patient_name;
         qDebug()<<"patient diseases: "<<diseases;
         ui->name->setText(patient_name);
         ui->disease->setText(diseases);

}

doctor_profile::~doctor_profile()
{
    delete ui;
}

void doctor_profile::connect_db(){
    db.setConnectOptions();
    db.setDatabaseName("Driver={SQL Server};Server=.\\SQLEXPRESS;Database=salamtak;Trusted_Connection=Yes;");
    if(db.open())
        qDebug()<<"data base opened successfully";
}

void doctor_profile::on_cancel_visits_clicked()
{
    for (auto it = visits_check_boxes.begin(); it != visits_check_boxes.end(); it++)
    {
        if((*it)->isChecked()){
            visits.push_back((*it)->text());
            query.exec(QString("UPDATE doctor_working_days SET available = 1 WHERE TheDate = '%1' AND national_id = %2;").arg((*it)->text()).arg(id));
            query.exec(QString("DELETE FROM visits WHERE TheDate = '%1' AND doctor_id = '%2';").arg((*it)->text()).arg(id));
            (*it)->hide();
        }
    }
    return;
}
