#ifndef SERVICE_CHOICE_H
#define SERVICE_CHOICE_H
#include "outpatient.h"
#include <QWidget>
namespace Ui {
class service_choice;
}

class service_choice : public QWidget
{
    Q_OBJECT

public:
    explicit service_choice(QWidget *parent = nullptr);
    ~service_choice();

private slots:
    void on_outpatient_button_clicked();

private:
    Ui::service_choice *ui;
    outpatient* outpatient_window;
};

#endif // SERVICE_CHOICE_H
