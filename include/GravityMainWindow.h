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
    void enableGUI(bool pEnabled);

signals:
    void newBall(QPoint pP1, int pRadius, double pMass, double pYvelocity, int pID);

protected slots:
    void on_resetButton_clicked();
    void on_startButton_clicked();
    void on_actionExit_triggered();


    //void on_pushButton_clicked();
    void on_mainDrawingWidget_newPointRequested(const QPoint &pPos);
    void on_comboBox_currentIndexChanged(int pIndex);
    void on_radiusSpinBox_valueChanged(int pValue);
    void on_massSpinBox_valueChanged(double pValue);
    void on_yVelocitySpinBox_valueChanged(double pValue);
    void on_xVelocitySpinBox_valueChanged(double pValue);
    void on_gravitySpinBox_valueChanged(double pValue);
    void on_timeStepSpinBox_valueChanged(double pValue);

    void updateGUI();
};

#endif // GRAVITYMAINWINDOW_H
