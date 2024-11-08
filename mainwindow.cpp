#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qurl.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , Escena(new QGraphicsScene(this))
    , Layout(new QGridLayout())
    , Nivel1(new QPushButton("Nivel 1"))
    , Nivel2(new QPushButton("Nivel 2"))
    , Fondo(new QGraphicsPixmapItem)
    , Nivel1P(new QGraphicsProxyWidget)
    , Nivel2P(new QGraphicsProxyWidget)
{
    ui->setupUi(this);
    this->resize(1280,800);
    srand(time(0));

    Escena->setSceneRect(0,0,1280,720);
    Vista = new QGraphicsView(Escena,this);
    Vista->setMinimumSize(1300,750);

    QWidget *Ventana = new QWidget(this);
    Ventana->setLayout(Layout);
    setCentralWidget(Ventana);

    Fondo->setPixmap(QPixmap("Menu Image.jpg"));

    Nivel1->setFixedSize(200,25);
    Nivel2->setFixedSize(200,25);

    Nivel1P->setWidget(Nivel1);
    Nivel2P->setWidget(Nivel2);

    Nivel1P->setPos(400,400);
    Nivel2P->setPos(700,400);

    Layout->addWidget(Vista,0,0);

    connect(Nivel1, &QPushButton::clicked, this, &MainWindow::LoadUTLevel);

    MainMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MainMenu(){
    Escena->setBackgroundBrush(Qt::NoBrush);
    Escena->addItem(Fondo);
    Escena->addItem(Nivel1P);
    Escena->addItem(Nivel2P);
    connect(Nivel1,&QPushButton::clicked,this,&MainWindow::LoadUTLevel);
}

void MainWindow::LoadUTLevel(){
    disconnect(Nivel1,&QPushButton::clicked,this,&MainWindow::LoadUTLevel);
    Escena->setBackgroundBrush(Qt::black);
    Escena->removeItem(Fondo);
    Escena->removeItem(Nivel1P);
    Escena->removeItem(Nivel2P);

    UnderTale* HomerFight = new UnderTale(Layout, Escena, "HomerFightBlack.png");
    connect(HomerFight, &UnderTale::ReturnToMainMenu, this, &MainWindow::MainMenu);
}
