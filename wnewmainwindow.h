#ifndef WNEWMAINWINDOW_H
#define WNEWMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class wnewMainWindow;
}

class wnewMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit wnewMainWindow(QWidget *parent = nullptr);
    ~wnewMainWindow();

private:
    Ui::wnewMainWindow *ui;
};

#endif // WNEWMAINWINDOW_H
