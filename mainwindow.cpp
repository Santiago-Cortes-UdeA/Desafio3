#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qurl.h>
#include <QDebug>
#include <fstream>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , Escena(new QGraphicsScene(this))
    , Layout(new QGridLayout())
    , Fondo(new QGraphicsPixmapItem)
    , Reproductor(new QMediaPlayer)
    , AudioOutput(new QAudioOutput)
    , CutScene(new QGraphicsVideoItem)
    , Info(new QLabel)
    , InfoP(new QGraphicsProxyWidget)
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

    for (int i = 0; i<4; i++){
        Botones.push_back(new QPushButton);
        Botones[i]->setAttribute(Qt::WA_TranslucentBackground);
    }

    for (int i = 0; i<4; i++){
        BotonesP.push_back(new QGraphicsProxyWidget);
        BotonesP[i]->setWidget(Botones[i]);
    }

    Botones[0]->setFixedSize(200,25);
    Botones[1]->setFixedSize(200,25);
    Botones[2]->setFixedSize(200,25);
    Botones[3]->setFixedSize(200,25);

    Botones[0]->setText("Nivel1");
    Botones[1]->setText("Nivel2");
    Botones[2]->setText("Logros");
    Botones[3]->setText("Regresar");

    /*QPixmap ButtonImage ("Button 1.png");
    Botones[0]->setIcon(QIcon(ButtonImage));
    Botones[0]->setIconSize(ButtonImage.size()/2);*/

    BotonesP[0]->setPos(200,400);
    BotonesP[1]->setPos(500,400);
    BotonesP[2]->setPos(800,400);
    BotonesP[3]->setPos(800,600);

    Layout->addWidget(Vista,0,0);

    Reproductor->setSource(QUrl("qrc:/Videos/Intro Cutscene.mp4"));
    Reproductor->setVideoOutput(CutScene);
    Reproductor->setAudioOutput(AudioOutput);
    QSize videoSize(1280,720);
    CutScene->setSize(videoSize);
    CutScene->setPos(0,0);
    Escena->addItem(CutScene);
    Reproductor->play();

    QPushButton* SaltarAnim = new QPushButton("Saltar Animacion");
    SaltarAnim->setFixedSize(200,25);
    QGraphicsProxyWidget* SaltarAnimP = new QGraphicsProxyWidget();
    SaltarAnimP->setWidget(SaltarAnim);
    SaltarAnimP->setPos(1080,695);
    Escena->addItem(SaltarAnimP);

    ifstream Data ("Achievements.txt");

    string Number;
    for (int i = 0; i<6; i++){
        Data.ignore(100,' ');
        getline(Data,Number);
        Stats[i]=stoi(Number);
    }

    Data.close();

    Info->setFont(QFont("Mars Needs Cunnilingus",20));
    Info->setAttribute(Qt::WA_TranslucentBackground);
    InfoP->setWidget(Info);
    InfoP->setPos(550, 300);

    connect(Botones[3], &QPushButton::clicked, this, &MainWindow::MainMenu);

    ConnectionA=connect(Reproductor, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::EndOfMedia){
            Escena->removeItem(SaltarAnimP);
            disconnect(ConnectionA);
            disconnect(ConnectionB);
            MainMenu();
        }
    });

    ConnectionB=connect(SaltarAnim, &QPushButton::clicked,this,[this, SaltarAnimP](){
        Reproductor->stop();
        disconnect(ConnectionA);
        disconnect(ConnectionB);
        Escena->removeItem(SaltarAnimP);
        MainMenu();
    });

    connect(Botones[0],&QPushButton::clicked,this,&MainWindow::LoadUTLevel);
    connect(Botones[1],&QPushButton::clicked,this,&MainWindow::LoadMountainLevel);
    connect(Botones[2],&QPushButton::clicked,this,&MainWindow::LoadAchievements);
    //Cambiar despues el conect de Botones[1] por el de cargar el Nivel2

}

MainWindow::~MainWindow()
{
    ofstream UpdateData ("Achievements.txt");
    for (int i = 0; i < 6; i++){
        switch (i){
        case 0:
            UpdateData<<"Nivel_1_Vencido ";
            break;
        case 1:
            UpdateData<<"Nivel_2_Vencido ";
            break;
        case 2:
            UpdateData<<"Nivel_1_NoHit ";
            break;
        case 3:
            UpdateData<<"Nivel_2_NoHit ";
            break;
        case 4:
            UpdateData<<"Nivel_1_MinimumDamageTaken ";
            break;
        case 5:
            UpdateData<<"Nivel_2_MinimumDamageTaken ";
            break;
        }
        UpdateData<<Stats[i]<<'\n';
    }
    delete ui;
}

void MainWindow::MainMenu(){
    Fondo->setPixmap(QPixmap("Menu Image.jpg"));
    Escena->setBackgroundBrush(Qt::NoBrush);
    if (Fondo->scene() == nullptr)Escena->addItem(Fondo);
    Escena->addItem(BotonesP[0]);
    Escena->addItem(BotonesP[1]);
    Escena->addItem(BotonesP[2]);
    if (BotonesP[3]->scene() != nullptr) Escena->removeItem(BotonesP[3]);
    if (InfoP->scene() != nullptr) Escena->removeItem(InfoP);
}

void MainWindow::LoadUTLevel(){
    Escena->removeItem(Fondo);
    Escena->removeItem(BotonesP[0]);
    Escena->removeItem(BotonesP[1]);
    Escena->removeItem(BotonesP[2]);

    UnderTale* HomerFight = new UnderTale(Escena, "HomerFight.png", Reproductor, 20);

    connect(HomerFight, &UnderTale::ReturnToMainMenu, this, [=](){
        int VidaRestante = HomerFight->getPlayerReference()->getVida();

        if (!Stats[2] && 20-VidaRestante == 0){
            Stats[2]=1;
        }

        if (!Stats[0] && VidaRestante>0){
            Stats[0]=1;
        }
        if (20 - VidaRestante < Stats[4]){
            Stats[4] = 20 - HomerFight->getPlayerReference()->getVida();
        }
        delete HomerFight;
        MainMenu();
        disconnect();
    });
}

void MainWindow::LoadMountainLevel(){
    Escena->removeItem(Fondo);
    Escena->removeItem(BotonesP[0]);
    Escena->removeItem(BotonesP[1]);
    Escena->removeItem(BotonesP[2]);

    new Mountain(Escena, "nivel2.png", Reproductor);
}

void MainWindow::LoadAchievements(){
    Fondo->setPixmap(QPixmap("Achievements Image.jpg"));
    Escena->removeItem(BotonesP[0]);
    Escena->removeItem(BotonesP[1]);
    Escena->removeItem(BotonesP[2]);
    Info->setText(QString
                  ("Vence el Nivel 1\n"
                   "Vence el Nivel 2\n"
                   "Vence el Nivel 1 sin ser golpeado\n"
                   "Vence el Nivel 2 sin ser golpeado\n"
                   "Minima cantidad de dano recibido en el Nivel 1: %1\n"
                   "Minima cantidad de dano recibido en el Nivel 2: %2")
                      .arg(Stats[0] == 1 ? QString::number(Stats[4]):"NAN",
                           Stats[1] == 1 ? QString::number(Stats[5]):"NAN"));
    Escena->addItem(BotonesP[3]);
    Escena->addItem(InfoP);
}
