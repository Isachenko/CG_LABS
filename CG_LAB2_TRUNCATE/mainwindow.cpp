#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _canvas = new Canvas(this);
    _canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->ui->horizontalLayout->insertWidget(0, _canvas);
    connect(this->ui->clearButton, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));
    connect(this->ui->generateButton, SIGNAL(clicked()), this, SLOT(onGenerateButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClearButtonClicked()
{
    _canvas->clear();
}

void MainWindow::onGenerateButtonClicked()
{
    QList<QPointF> windowPoints;
    windowPoints.append(QPointF(10, 10));
    windowPoints.append(QPointF(10, 500));
    windowPoints.append(QPointF(500, 500));
    windowPoints.append(QPointF(500, 10));
    _canvas->setWindowPoints(windowPoints);

    QList<QPointF> objectPoints;
    objectPoints.append(QPointF(9, 9));
    objectPoints.append(QPointF(250, 5));
    objectPoints.append(QPointF(600, 20));
    objectPoints.append(QPointF(700, 200));
    objectPoints.append(QPointF(300, 510));
    objectPoints.append(QPointF(6, 300));
    _canvas->setObjectPoints(objectPoints);
}
