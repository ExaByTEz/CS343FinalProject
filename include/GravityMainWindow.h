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
    QTimer *timer;
    bool mStartSimulation = false;
    int mNumItems = 0;
    int mActiveIndex = -1;

signals:
    void newBall(QPoint pP1, int pID);

protected slots:
    void on_pushButton_clicked();
    void on_mainDrawingWidget_newPointRequested(const QPoint &pPos);
    void on_comboBox_currentIndexChanged(int pIndex);
    void updateGUI();
};

#endif // GRAVITYMAINWINDOW_H
