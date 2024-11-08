#include "undertale.h"

UnderTale::UnderTale(QGridLayout *&Layout, QGraphicsScene*& Escena, QString FileName):Nivel(Escena, FileName, Layout), AtkDuration(new QTimer(this)), Spawn(new QTimer(this)), CutScene(new QGraphicsVideoItem), Reproducir(new QPushButton("Iniciar Pelea")){
    Reproductor->setSource(QUrl("qrc:/Videos/Starting Cutscene.mp4"));
    Reproductor->setVideoOutput(CutScene);
    Reproductor->setAudioOutput(AudioOutput);
    QSize videoSize(1280,720);
    CutScene->setSize(videoSize);
    CutScene->setPos(0,0);
    Escena->addItem(CutScene);
    Reproductor->play();

    Caja = new QGraphicsRectItem(390,300,500,300);
    QPen borde = QPen(Qt::white);
    borde.setWidth(10);
    Caja->setPen(borde);
    Caja->setBrush(Qt::NoBrush);

    Reproducir->setGeometry(0,0,300,50);
    Reproducir->setFixedSize(300,25);

    connect(Jugador, &Alma::gameOver, this, &UnderTale::GameOver);

    connect(Reproducir, &QPushButton::clicked,this,&UnderTale::StartGame);
    OtherConnection = connect(Reproductor, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::EndOfMedia){
            StartGame();
        }
    });

    Atk = AtaqueActivo::Ninguno;
    Layout->addItem(new QSpacerItem(0, 12, QSizePolicy::Minimum, QSizePolicy::Expanding),0,0);
    Layout->addWidget(Reproducir,12,0);
}

UnderTale::~UnderTale(){
    if (OtherConnection) disconnect(OtherConnection);
    delete AtkDuration;
    delete Spawn;
    delete CutScene;
    delete Caja;
    delete Reproducir;
    delete Jugador;
    delete AudioOutput;
    delete Reproductor;
    delete BackGround;
}
//____________________________________START/STOP GAME____________________________________//

void UnderTale::StartGame(){

    Jugador->Reset();
    Reproductor->setSource(QUrl("qrc:/Canciones/Megalo.mp3"));
    Reproductor->setAudioOutput(AudioOutput);
    Reproductor->play();
    BackGround->setPos(210,0);
    Escena->addItem(BackGround);
    Escena->addItem(Jugador);
    Jugador->addHealthBar();
    Jugador->setFocus();
    Escena->addItem(Caja);

    AtkDuration->start(2500);
    connect(AtkDuration, &QTimer::timeout, this, &UnderTale::AttackPattern);
    disconnect(OtherConnection);
}

void UnderTale::StopGame(){

}

//____________________________________GAME OVER____________________________________//

void UnderTale::GameOver(){
    AtkDuration->stop();
    Reproductor->stop();
    StopSpawn(*this);
    Escena->removeItem(BackGround);
    Jugador->removeHealthBar();
    Escena->removeItem(Caja);
    if (AtkConnection) disconnect(AtkConnection);
    disconnect(AtkDuration, &QTimer::timeout, this, &UnderTale::AttackPattern);
    Atk=AtaqueActivo::Ninguno;
    AtkDuration->start(2000);
    AtkConnection = connect (AtkDuration, &QTimer::timeout, this, &UnderTale::GameOverTransition);
}

void UnderTale::GameOverTransition(){
    AtkDuration->stop();
    qDebug()<<"Game Over";
    disconnect(AtkConnection);

    Reproductor->setSource(QUrl("qrc:/Canciones/Determination.mp3"));

    Spawn->start(50);
    AtkConnection=connect(Spawn, &QTimer::timeout, Jugador, &Alma::MoveToCenter);
    connect(Jugador, &Alma::Center, this, &UnderTale::GameOverMenu);
}

void UnderTale::GameOverMenu(){
    Reproductor->play();
    Spawn->stop();
    disconnect(AtkConnection);
    disconnect(Jugador, &Alma::Center, this, &UnderTale::GameOverMenu);
    QGraphicsTextItem* GAMEOVER = new QGraphicsTextItem();
    GAMEOVER->setPlainText(QString("GAME OVER"));
    GAMEOVER->setFont(QFont("Mars Needs Cunnilingus", 50));
    GAMEOVER->setPos(200,50);
    Escena->addItem(GAMEOVER);
}

//____________________________________ATTACKS____________________________________//

void Ataque1(UnderTale& UT){
    UT.Spawn->start(750);
    UT.AtkConnection=UnderTale::connect(UT.Spawn, &QTimer::timeout, &UT, &UnderTale::lluviaDeDonas);
}

void Ataque2(UnderTale& UT){
    UT.Spawn->start(1250);
    UT.AtkConnection=UnderTale::connect(UT.Spawn, &QTimer::timeout, &UT, &UnderTale::generarBlaster);
}

void Ataque3(UnderTale& UT){
    UT.Spawn->start(200);
    UnderTale::connect(UT.Jugador, &Alma::gameOver, UT.Spawn, &QTimer::stop);
    UT.AtkConnection=UnderTale::connect(UT.Spawn, &QTimer::timeout, &UT, [&UT](){
        UT.DuffRound(UT.Angulo);
        UT.Angulo+=15;
    });
}

void Ataque4(UnderTale& UT){
    Cerveza * Beer = new Cerveza(UT.Jugador,390,565,5,UT.Escena,UT.AtkDuration);
    UnderTale::connect(Beer, &Cerveza::tope, &UT, [&UT](){
        UT.Spawn->start(1000);
    });
    UT.AtkConnection=UnderTale::connect(UT.Spawn, &QTimer::timeout, &UT, &UnderTale::Burbujas);
}

void StopSpawn(UnderTale& UT){
    UT.Spawn->stop();
    switch (UT.Atk){
    case (UnderTale::AtaqueActivo::Ninguno):
        break;
    default:
        UnderTale::disconnect(UT.AtkConnection);
    }
}

void UnderTale::lluviaDeDonas(){
    int x = (rand()%451)+390;
    new MeleeAT (Jugador,x,250,4,Escena,"Dona2.png",20,100,270);
}

void UnderTale::generarBlaster(){
    int Direccion = (rand()%3)+1;
    qreal Angulo = Direccion * 90;
    if (Direccion%2==0){
        new Blaster (Jugador, Escena, Jugador->getx()+15,445+(200*qCos(qDegreesToRadians(Angulo))), Angulo);
    }
    else{
        new Blaster (Jugador, Escena, 630-(300*qSin(qDegreesToRadians(Angulo))),Jugador->gety(), Angulo);
    }
}

void UnderTale::DuffRound(qreal& Angulo){
    new Blaster (Jugador, Escena, 645-(250*qSin(qDegreesToRadians(Angulo))),445+(250*qCos(qDegreesToRadians(Angulo))), Angulo);
}

void UnderTale::Burbujas(){
    int x = 490;
    for (int i = 0; i<4; i++){
        new Burbuja(Jugador, x+(i*75)+(rand()%201)-100,475,2,Escena,"Burbuja.png",10+rand()%6,150,rand()%181);
    }
}

void UnderTale::AttackPattern(){
    if (Atk == AtaqueActivo::Ninguno) {
        Ataque1(*this);
        Atk = AtaqueActivo::ATK1;
        AtkDuration->start(10000);
    }
    else if (Atk == AtaqueActivo::ATK1) {
        StopSpawn(*this);
        Ataque2(*this);
        Atk = AtaqueActivo::ATK2;
        AtkDuration->start(7500);
    }
    else if (Atk == AtaqueActivo::ATK2) {
        Angulo = 0;
        StopSpawn(*this);
        Ataque3(*this);
        Atk = AtaqueActivo::ATK3;
        AtkDuration->start(15000);
    }
    else if (Atk == AtaqueActivo::ATK3) {
        StopSpawn(*this);
        Ataque4(*this);
        Atk = AtaqueActivo::ATK4;
        AtkDuration->start(15000);
    }
    else if (Atk == AtaqueActivo::ATK4) {
        StopSpawn(*this);
        Atk = AtaqueActivo::Ninguno;
        AtkDuration->stop();
        Reproductor->stop();
        Escena->removeItem(BackGround);
        Escena->removeItem(Jugador);
        Jugador->removeHealthBar();
        Escena->removeItem(Caja);
        disconnect(AtkConnection);
        disconnect(Reproducir, &QPushButton::clicked,this,&UnderTale::StartGame);
        Layout->removeWidget(Reproducir);
        disconnect(AtkDuration, &QTimer::timeout, this, &UnderTale::AttackPattern);
        Reproductor->setSource(QUrl("qrc:/Videos/Final Cutscene.mp4"));
        Reproductor->play();
        OtherConnection = connect(Reproductor, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status){
            if (status == QMediaPlayer::EndOfMedia){
                emit ReturnToMainMenu();
                delete this;
            }
        });
    }
}
