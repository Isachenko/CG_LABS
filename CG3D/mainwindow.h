#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QSlider>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "letter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void moveX(int k) {
        letter->setMoveX(k);
        letter->repaint();
    }
    void moveY(int k) {
        letter->setMoveY(k);
        letter->repaint();
    }
    void moveZ(int k) {
        letter->setMoveZ(k);
        letter->repaint();
    }
    void changeXScale(int k) {
        letter->changeXScale(k / 10.0);
        letter->repaint();
    }
    void changeYScale(int k) {
        letter->changeYScale(k / 10.0);
        letter->repaint();
    }
    void changeZScale(int k) {
        letter->changeZScale(k / 10.0);
        letter->repaint();
    }
private:
    void initLetter();
    void initSliders();



    QVBoxLayout * slidersLayout;
    QSlider * moveXSlider;
    QSlider * moveYSlider;
    QSlider * moveZSlider;    
    QSlider * scaleXSlider;
    QSlider * scaleYSlider;
    QSlider * scaleZSlider;
    Letter * letter;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
