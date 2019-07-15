#include "wnewmainwindow.h"
#include "ui_wnewmainwindow.h"

wnewMainWindow::wnewMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wnewMainWindow)
{
    ui->setupUi(this);
}

wnewMainWindow::~wnewMainWindow()
{
    delete ui;
}
