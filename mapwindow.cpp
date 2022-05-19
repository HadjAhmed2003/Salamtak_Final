#include "mapwindow.h"
#include "ui_mapwindow.h"
//#include <QtWebEngineWidgets/QWebEngineView>
//#include <QtWebEngineWidgets/QWebEnginePage>
//#include <QtWebEngineWidgets/QWebEngineSettings>
mapWindow::mapWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mapWindow)
{
    ui->setupUi(this);
//    QWebEngineView* webview = new QWebEngineView;
//    QUrl url = QUrl("qrc:/map.html");
//    webview->page()->load(url);
//    ui->verticalLayout->addWidget(webview);
}

mapWindow::~mapWindow()
{
    delete ui;
}
