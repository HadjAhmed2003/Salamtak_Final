#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QWidget>

namespace Ui {
class mapWindow;
}

class mapWindow : public QWidget
{
    Q_OBJECT

public:
    explicit mapWindow(QWidget *parent = nullptr);
    ~mapWindow();

private:
    Ui::mapWindow *ui;
};

#endif // MAPWINDOW_H
