#ifndef GRAVITYMAINWINDOW_H
#define GRAVITYMAINWINDOW_H

#include <QMainWindow>
#include <QPoint>

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

signals:
    void newBall(QPoint pP1);

protected slots:
    void on_pushButton_clicked();
    void on_mainDrawingWidget_newPointRequested(const QPoint &pPos);
};

#endif // GRAVITYMAINWINDOW_H
