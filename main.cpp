#include "hellowidget.h"
#include "toolwidget.h"
#include <QApplication>
#include<QPushButton>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HelloWidget w;
    w.resize(600,450);
    w.show();

    return a.exec();
}
