#include "service_choice.h"
#include "ui_service_choice.h"

service_choice::service_choice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::service_choice)
{
    ui->setupUi(this);
}

service_choice::~service_choice()
{
    delete ui;
}

void service_choice::on_outpatient_button_clicked()
{
    outpatient_window = new outpatient();
    this->hide();
    outpatient_window->email = patient_email;
    outpatient_window->show();
}

