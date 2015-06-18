#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QPointF>
#include "drawcanvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QVector<QPointF> _allPoints;

    DrawCanvas* _canvas;
    QVector<QPointF> generatePoints(int count, qreal maxX, qreal maxY);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
