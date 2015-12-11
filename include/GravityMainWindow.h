#ifndef GRAVITYMAINWINDOW_H
#define GRAVITYMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class GravityMainWindow;
}

class GravityMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GravityMainWindow(QWidget *parent = 0);
    ~GravityMainWindow();

private:
    Ui::GravityMainWindow *ui;

protected slots:
    void on_resetButton_clicked();
    void on_startButton_clicked();
    void on_actionExit_triggered();
};

#endif // GRAVITYMAINWINDOW_H
