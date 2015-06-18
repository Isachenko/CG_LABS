#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "splineengine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SplineEngine::initMatrix();
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
    QVector<QPointF> windowPoints;
    windowPoints.append(QPointF(10, 10));
    windowPoints.append(QPointF(10, 500));
    windowPoints.append(QPointF(500, 500));
    windowPoints.append(QPointF(500, 10));
    _canvas->setControlPoints(windowPoints);
}
