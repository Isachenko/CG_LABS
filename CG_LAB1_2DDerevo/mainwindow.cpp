#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGlobal.h>
#include <QTime>
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create canvas
    _canvas = new DrawCanvas();
    QPushButton* btn = new QPushButton();
    QHBoxLayout* layout = new QHBoxLayout(this);
    this->ui->centralWidget->setLayout(layout);
    layout->addWidget(_canvas);

    this->resize(600, 600);

    //generaePoints
    _allPoints = generatePoints(50000, _canvas->width(), _canvas->height());

    //drawPoint
    _canvas->setPointsToDraw(_allPoints);
    _canvas->update();
    _canvas->setAutoFillBackground(true);
    //signals
    connect(this->ui->actionEraseRect, &QAction::triggered, [this]() {
        this->_canvas->eraseRect();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<QPointF> MainWindow::generatePoints(int count, qreal maxX, qreal maxY)
{
    QVector<QPointF> points;
    for(int i = 0; i < count; ++i){
        qreal x = qrand() % ((int)maxX + 1) ;
        qreal y = qrand() % ((int)maxY + 1) ;
        QPointF point(x, y);
        points.append(point);
    }
    return points;
}
