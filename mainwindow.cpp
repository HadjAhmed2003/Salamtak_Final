#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "patient_sign_up.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sign_up_clicked()
{
    if((ui->patient->isChecked())||(ui->doctor->isChecked())||((ui->receptionist->isChecked()))){
        if(ui->patient->isChecked()){
            patient_window = new patient_sign_up();
            this->hide();
            patient_window->show();
        }else if(ui->doctor->isChecked()){
            doctor_signup_window = new doctor_sign_up();
            this->hide();
            doctor_signup_window->show();
        }
    }else{
        ui->validation->setText("Choose type of user");
    }
}


void MainWindow::on_sign_in_clicked()
{
    if((ui->patient->isChecked())||(ui->doctor->isChecked())||((ui->receptionist->isChecked()))){
        if(ui->patient->isChecked()){
            sign_in_window = new sign_in("patient");
            this->hide();
            sign_in_window->patient = true;
            sign_in_window->show();
        }
        if(ui->doctor->isChecked()){
            sign_in_window = new sign_in("doctors"); //it's written doctors because in the db a table is called doctors_info and we use this parameter to determine which table by adding _info
            this->hide();
            sign_in_window->patient = true;
            sign_in_window->show();
        }
    }else{
        ui->validation->setText("Choose type of user");
    }
}

