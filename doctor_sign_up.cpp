#include "doctor_sign_up.h"
#include "ui_doctor_sign_up.h"
#include <QScrollArea>
#include <QCheckBox>
doctor_sign_up::doctor_sign_up(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::doctor_sign_up)
{
    ui->setupUi(this);
    for(int i=0; i<7; i++){
        days_check_box[i] = new QCheckBox();
    }
    days_check_box[0]->setText("Sunday");
    days_check_box[1]->setText("Moday");
    days_check_box[2]->setText("Tuesday");
    days_check_box[3]->setText("Wednesday");
    days_check_box[4]->setText("Thursday");
    days_check_box[5]->setText("Friday");
    days_check_box[6]->setText("Saturday");
    ui->specialization->addItem("Dermatology");
    ui->specialization->addItem("Neurology");
    ui->specialization->addItem("Pathology");
    ui->price->setValidator( new QIntValidator(0, 100, this) );
    QScrollArea* scrollArea = new QScrollArea(ui->days);
    scrollArea->setWidgetResizable(true);
    scrollArea->setGeometry(QRect(0,0, 450, 150));
    QWidget* checkboxes = new QWidget(scrollArea);
    QVBoxLayout* layout = new QVBoxLayout(checkboxes);
//    layout->setGeometry(QRect(0,0, 100, 100));
    for (int i = 0; i < 7; ++i)
    {
       layout->addWidget(days_check_box[i]);
      }
     scrollArea->setWidget(checkboxes);
    connect_db();
}

doctor_sign_up::~doctor_sign_up()
{
    delete ui;
}

void doctor_sign_up::connect_db(){
    db.setConnectOptions();
    db.setDatabaseName("Driver={SQL Server};Server=.\\SQLEXPRESS;Database=salamtak;Trusted_Connection=Yes;");
    if(db.open())
        qDebug()<<"data base opened successfully";
}

void doctor_sign_up::on_submit_clicked()
{
    //get data
    first_name = ui->first_name->text();
    last_name = ui->last_name->text();
    email = ui->email->text();
    password_doctor = ui->password->text();
    phone_number = ui->phone_number->text();
    national_id = ui->national_id->text();
    specialization = ui->specialization->currentText();
    price_str = ui->price->text();
    if(price_str != "")
        price = (ui->price->text()).toInt();
    if((ui->female->isChecked())||(ui->male->isChecked())){
        if(ui->female->isChecked()){
            gender = ui->female->text();
        }else{
            gender = ui->male->text();
        }
    }
    int count =0;
    for(int i=0; i<7; i++){
        if(days_check_box[i]->isChecked()){
            count++;
        }
    }
    if(count==0){
        ui->validation->setText("Please select your working days");
    }
    //end of get data

    //checking for blank fields
    bool blank = ((first_name=="")||(last_name=="")||(email=="")||(password_doctor=="")||(national_id=="")||(phone_number==""));
    if(blank){
        ui->validation->setText("Fill out all the info");
        return;
    }
    //end of checking for blank fieds
    else{
        query.exec(QString("SELECT national_id FROM doctors_info WHERE national_id='%1'").arg(national_id));
        query.next();
        QString temp_national_id = query.value(0).toString();
        query.exec(QString("SELECT email FROM doctors_info WHERE email='%1'").arg(email));
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
            query.exec(QString("INSERT INTO doctors_info VALUES('%1','%2','%3','%4','%5','%6','%7',%8,'%9')").arg(first_name).arg(last_name).arg(gender).arg(email).arg(password_doctor).arg(phone_number).arg(specialization).arg(price_str).arg(national_id));
            for(int i=0; i<7; i++){
                if(days_check_box[i]->isChecked()){
                    query.exec(QString("INSERT INTO doctor_working_days (TheDayName, TheDate)SELECT TheDayName, TheDate From  DateDimension WHERE TheDayName = '%1';").arg(days_check_box[i]->text()));
                    query.exec(QString("update doctor_working_days set national_id = '%1', available = 'true' where national_id IS NULL;").arg(national_id));
                }
            }
            db.close();
            this->hide();
            sign_in_window= new sign_in();
            sign_in_window->doctor=true;
            sign_in_window->show();
        }
    }
}


