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
    connect(this->ui->showMoreButton, SIGNAL(clicked()), this, SLOT(onShowMoreButtonClicked()));
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
    QList<QPointF> points;
    int pointsCount = this->ui->spinBox->value();
    for(int i = 0; i < pointsCount; ++i) {
        int x = 50 + (qrand() % 500);
        int y = 20 + (qrand() % 500);
        points.append(QPointF(x, y));
    }
    _canvas->setPoints(points);
}

void MainWindow::onShowMoreButtonClicked()
{
    _canvas->setShowExampleInfo(!_canvas->showExampleInfo());
    _canvas->update();
}
