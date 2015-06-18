#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
    setWindowTitle("Letter");
    setFixedSize(800, 500);
    initSliders();
    initLetter();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initLetter()
{

    letter = new Letter();
    //letter->setFixedSize(500, 500);
    ui->mainLayout->addWidget(letter);
}

void MainWindow::initSliders(){
    slidersLayout = new QVBoxLayout;        

    slidersLayout->addWidget(new QLabel("move x:", this));
    moveXSlider = new QSlider(Qt::Horizontal);
    moveXSlider->setFocusPolicy(Qt::StrongFocus);
    moveXSlider->setSingleStep(0.3);
    moveXSlider->setMaximum(10);
    moveXSlider->setMinimum(-10);
    moveXSlider->setValue(0);
    connect(moveXSlider, SIGNAL(valueChanged(int)), this, SLOT(moveX(int)));
    slidersLayout->addWidget(moveXSlider);

    slidersLayout->addWidget(new QLabel("move y:", this));
    moveYSlider = new QSlider(Qt::Horizontal);
    moveYSlider->setFocusPolicy(Qt::StrongFocus);
    moveYSlider->setSingleStep(0.3);
    moveYSlider->setMaximum(10);
    moveYSlider->setMinimum(-10);
    moveYSlider->setValue(0);
    connect(moveYSlider, SIGNAL(valueChanged(int)), this, SLOT(moveY(int)));
    slidersLayout->addWidget(moveYSlider);

    slidersLayout->addWidget(new QLabel("move z:", this));
    moveZSlider = new QSlider(Qt::Horizontal);
    moveZSlider->setFocusPolicy(Qt::StrongFocus);
    moveZSlider->setSingleStep(0.3);
    moveZSlider->setMaximum(10);
    moveZSlider->setMinimum(-10);
    moveZSlider->setValue(0);
    connect(moveZSlider, SIGNAL(valueChanged(int)), this, SLOT(moveZ(int)));
    slidersLayout->addWidget(moveZSlider);

    slidersLayout->addWidget(new QLabel("scale x:", this));
    scaleXSlider = new QSlider(Qt::Horizontal);
    scaleXSlider->setFocusPolicy(Qt::StrongFocus);
    scaleXSlider->setSingleStep(0.3);
    scaleXSlider->setMaximum(15);
    scaleXSlider->setMinimum(1);
    scaleXSlider->setValue(10);
    connect(scaleXSlider, SIGNAL(valueChanged(int)), this, SLOT(changeXScale(int)));
    slidersLayout->addWidget(scaleXSlider);

    slidersLayout->addWidget(new QLabel("scale y:", this));
    scaleYSlider = new QSlider(Qt::Horizontal);
    scaleYSlider->setFocusPolicy(Qt::StrongFocus);
    scaleYSlider->setSingleStep(0.3);
    scaleYSlider->setMaximum(15);
    scaleYSlider->setMinimum(1);
    scaleYSlider->setValue(10);
    connect(scaleYSlider, SIGNAL(valueChanged(int)), this, SLOT(changeYScale(int)));
    slidersLayout->addWidget(scaleYSlider);

    ui->mainLayout->addLayout(slidersLayout);   

    this->autoFillBackground();

    //layout->addWidget(stacked);
    //layout->addWidget(slider);
}


