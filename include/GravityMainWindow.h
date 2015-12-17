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
    // instance of application window
    Ui::GravityMainWindow *ui;
    // timer for simulation
    QTimer *timer;
    // bool to show is simulation is running
    bool mStartSimulation = false;
    // counter for number of items on screen
    int mNumItems = 0;
    // index of currently selected ball
    int mActiveIndex = -1;
    void enableGUI(bool pEnabled);

signals:
    // signal for new ball object
    void newBall(QPoint pP1, int pRadius, double pMass, double pYvelocity, int pID);

protected slots:
    // slot for reset button
    void on_resetButton_clicked();
    // slot for start button
    void on_startButton_clicked();
    // slot for exit option in menu
    void on_actionExit_triggered();

    // slot for new selected point in render area
    void on_mainDrawingWidget_newPointRequested(const QPoint &pPos);
    // slot for current ball object shown in combo box
    void on_comboBox_currentIndexChanged(int pIndex);
    // slot for current radius value
    void on_radiusSpinBox_valueChanged(int pValue);
    // slot for current mass value
    void on_massSpinBox_valueChanged(double pValue);
    // slot for current y velocity value
    void on_yVelocitySpinBox_valueChanged(double pValue);
    // slot for current x velocity value
    void on_xVelocitySpinBox_valueChanged(double pValue);
    // slot for current gravity value
    void on_gravitySpinBox_valueChanged(double pValue);
    // slot for current time step value
    void on_timeStepSpinBox_valueChanged(double pValue);

    void updateGUI();
};

#endif // GRAVITYMAINWINDOW_H
