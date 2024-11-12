#include "undertale.h"

UnderTale::UnderTale(QGridLayout *&Layout, QGraphicsScene*& Escena, QString FileName, QMediaPlayer *&Reproductor_)
    :Nivel(Escena, FileName, Layout, Reproductor_)
    , AtkDuration(new QTimer(this))
    , AtkDelay(new QTimer(this))
    , Spawn(new QTimer(this))
    , Reproducir(new QPushButton("Iniciar Pelea"))
    , GAMEOVER(new QGraphicsTextItem)

{
    Escena->setBackgroundBrush(Qt::black);

    Reproductor->setSource(QUrl("qrc:/Videos/Starting Cutscene.mp4"));

    Reproductor->play();

    AtkDuration->setSingleShot(true);
    AtkDelay->setSingleShot(true);

    Caja = new QGraphicsRectItem(390,300,500,300);
    QPen borde = QPen(Qt::white);
    borde.setWidth(10);
    Caja->setPen(borde);
    Caja->setBrush(Qt::NoBrush);

    Reproducir->setGeometry(0,0,300,50);
    Reproducir->setFixedSize(300,25);
    QGraphicsProxyWidget* ReproducirP = new QGraphicsProxyWidget;
    ReproducirP->setWidget(Reproducir);
    ReproducirP->setPos(0,700);
    Escena->addItem(ReproducirP);

    QPushButton* Boton1 = new QPushButton("Reintentar");
    QGraphicsProxyWidget* Boton1P = new QGraphicsProxyWidget();
    Boton1->setFixedSize(400,35);
    Boton1->setFont(QFont("Mars Needs Cunnilingus", 30));
    Boton1P->setWidget(Boton1);
    Boton1P->setPos(200,500);

    QPushButton* Boton2 = new QPushButton("Volver al Menu");
    QGraphicsProxyWidget* Boton2P = new QGraphicsProxyWidget();
    Boton2->setFont(QFont("Mars Needs Cunnilingus", 30));
    Boton2->setFixedSize(400,35);
    Boton2P->setWidget(Boton2);
    Boton2P->setPos(700,500);

    BotonesP.push_back(Boton1P);
    BotonesP.push_back(Boton2P);

    connect(Boton1, &QPushButton::clicked, this, &UnderTale::StartGame);
    connect(Boton2, &QPushButton::clicked, this, [=](){
        emit ReturnToMainMenu();
        ClearAll();
        this->deleteLater();
        disconnect();
    });

    connect(Jugador, &Alma::gameOver, this, &UnderTale::GameOver);

    AtkConnection = connect(Reproducir, &QPushButton::clicked,this,[=](){
        StartGame();
        Escena->removeItem(ReproducirP);
    });
    OtherConnection = connect(Reproductor, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::EndOfMedia){
            StartGame();
            Escena->removeItem(ReproducirP);
        }
    });

    Atk = AtaqueActivo::Ninguno;

    GAMEOVER->setPlainText(QString("GAME OVER"));
    GAMEOVER->setFont(QFont("Mars Needs Cunnilingus", 50));
    GAMEOVER->setPos(400,70);

    connect(AtkDelay, &QTimer::timeout, this, &UnderTale::AttackPattern);
}

UnderTale::~UnderTale(){
    if (OtherConnection) disconnect(OtherConnection);
    disconnect(Reproducir, &QPushButton::clicked,this,&UnderTale::StartGame);
    delete AtkDuration;
    delete Spawn;
    delete Caja;
    delete Reproducir;
    delete Jugador;
    delete BackGround;
}
//____________________________________START GAME____________________________________//

void UnderTale::StartGame(){

    if (BotonesP[0]->scene() != nullptr) Escena->removeItem(BotonesP[0]);
    if (BotonesP[1]->scene() != nullptr) Escena->removeItem(BotonesP[1]);
    if (Jugador->scene() == nullptr) Escena->addItem(Jugador);
    if (GAMEOVER->scene() != nullptr) Escena->removeItem(GAMEOVER);
    Jugador->Reset();
    Reproductor->setSource(QUrl("qrc:/Canciones/Megalo.mp3"));
    Reproductor->play();
    BackGround->setPos(210,0);
    Escena->addItem(BackGround);
    Jugador->addHealthBar();
    Jugador->setFocus();
    Escena->addItem(Caja);

    AtkDelay->start(2500);

    disconnect(OtherConnection);
    disconnect(AtkConnection);
    disconnect(Reproducir, &QPushButton::clicked,this,&UnderTale::StartGame);
    OtherConnection=connect(AtkDuration, &QTimer::timeout, this, &UnderTale::StopSpawn);
}

//____________________________________GAME OVER____________________________________//

void UnderTale::GameOver(){
    AtkDuration->stop();
    AtkDelay->stop();
    Reproductor->stop();
    StopSpawn();
    Escena->removeItem(BackGround);
    Jugador->removeHealthBar();
    Escena->removeItem(Caja);
    if (AtkConnection) disconnect(AtkConnection);
    disconnect(OtherConnection);
    Atk=AtaqueActivo::Ninguno;
    AtkDuration->start(2000);
    OtherConnection = connect (AtkDuration, &QTimer::timeout, this, &UnderTale::GameOverTransition);
}

void UnderTale::GameOverTransition(){
    qDebug()<<"Game Over";
    disconnect(OtherConnection);

    Reproductor->setSource(QUrl("qrc:/Canciones/Determination.mp3"));

    Spawn->start(50);
    OtherConnection=connect(Spawn, &QTimer::timeout, Jugador, &Alma::MoveToCenter);
    connect(Jugador, &Alma::Center, this, &UnderTale::GameOverMenu);
}

void UnderTale::GameOverMenu(){
    Reproductor->play();
    Spawn->stop();
    disconnect(OtherConnection);
    disconnect(Jugador, &Alma::Center, this, &UnderTale::GameOverMenu);

    Escena->addItem(GAMEOVER);

    Escena->addItem(BotonesP[0]);
    Escena->addItem(BotonesP[1]);
}

//____________________________________ATTACKS____________________________________//

    //____________________________________ATTACK CONNECTIONS____________________________________//

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
    UT.AtkConnection=UnderTale::connect(UT.Spawn, &QTimer::timeout, &UT, [&UT](){
        UT.DuffRound(UT.NumVar);
        UT.NumVar+=15;
    });
}

void Ataque4(UnderTale& UT){
    Cerveza * Beer = new Cerveza(UT.Jugador,390,565,5,UT.Escena,UT.AtkDuration);
    UT.AtkConnection=UnderTale::connect(Beer, &Cerveza::tope, &UT, [&UT](){
        UT.Spawn->start(1000);
    });
    UnderTale::connect(UT.Spawn, &QTimer::timeout, &UT, &UnderTale::Burbujas);
}

void Ataque5(UnderTale& UT){
    UT.Spawn->start(1500);
    UT.AtkConnection=UnderTale::connect(UT.Spawn, &QTimer::timeout, &UT, &UnderTale::BeerJump);
}

void Ataque6(UnderTale& UT){
    UT.Spawn->start(500);
    UT.AtkConnection=UnderTale::connect(UT.Spawn, &QTimer::timeout, &UT, [&UT](){
        UT.BlueBeer(UT.NumVar);
        UT.NumVar+=1;
    });
}

    //____________________________________ATTACK TIMER____________________________________//

void UnderTale::StopSpawn(){
    Spawn->stop();
    switch (Atk){
    case (UnderTale::AtaqueActivo::Ninguno):
        break;
    default:
        UnderTale::disconnect(AtkConnection);
    }
}

    //____________________________________ATTACK PATTERNS____________________________________//

void UnderTale::lluviaDeDonas(){
    int x = (rand()%451)+390;
    new MeleeAT (Jugador,x,250,4,Escena,"Dona2.png",false,20,100,270);
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
        new Burbuja(Jugador, x+(i*75)+(rand()%201)-100,475,2,Escena,"Burbuja.png",false,10+rand()%6,150,rand()%181);
    }
}

void UnderTale::BeerJump(){
    new MeleeAT(Jugador, 390, 475, 4, Escena, "Botella.png", false, 10, 50, 0);
    new MeleeAT(Jugador, 890, 475, 4, Escena, "Botella.png", false, 10, 50, 180);
}

void UnderTale::BlueBeer(qreal &SpawnedNumber){
    if (SpawnedNumber<=12){
        if (int(SpawnedNumber)%2==0){
            new MeleeAT(Jugador, 890, 540, 5, Escena, "Dona2.png", false, 15, 30, 180);
            new MeleeAT(Jugador, 890, 570, 5, Escena, "Dona2.png", false, 15, 30, 180);
        }
        else{
            new MeleeAT(Jugador, 890, 475, 5, Escena, "Botella.png", true, 15, 30, 180);
            new MeleeAT(Jugador, 890, 375, 5, Escena, "Botella.png", true, 15, 30, 180);
        }
    }
    else{
        if (int(SpawnedNumber)%2==1){
            new MeleeAT(Jugador, 390, 540, 5, Escena, "Dona2.png", false, 15, 30, 0);
            new MeleeAT(Jugador, 390, 570, 5, Escena, "Dona2.png", false, 15, 30, 0);
        }
        else{
            new MeleeAT(Jugador, 390, 475, 5, Escena, "Botella.png", true, 15, 30, 0);
            new MeleeAT(Jugador, 390, 375, 5, Escena, "Botella.png", true, 15, 30, 0);
        }
    }
}

    //____________________________________ATTACK SEQUENCE____________________________________//

void UnderTale::AttackPattern(){
    if (Atk == AtaqueActivo::Ninguno) {
        Ataque1(*this);
        Atk = AtaqueActivo::ATK1;
        AtkDuration->start(10000);
        AtkDelay->start(11000);
    }
    else if (Atk == AtaqueActivo::ATK1) {
        Ataque2(*this);
        Atk = AtaqueActivo::ATK2;
        AtkDuration->start(7500);
        AtkDelay->start(8000);
    }
    else if (Atk == AtaqueActivo::ATK2) {
        NumVar = 0;
        Ataque3(*this);
        Atk = AtaqueActivo::ATK3;
        AtkDuration->start(15000);
        AtkDelay->start(18000);
    }
    else if (Atk == AtaqueActivo::ATK3) {
        Ataque4(*this);
        Atk = AtaqueActivo::ATK4;
        AtkDuration->start(15000);
        AtkDelay->start(18000);
    }
    else if (Atk == AtaqueActivo::ATK4) {
        disconnect(Spawn, &QTimer::timeout, this, &UnderTale::Burbujas);
        Jugador->changeSoulMode();
        Ataque5(*this);
        Atk = AtaqueActivo::ATK5;
        AtkDuration->start(20000);
        AtkDelay->start(22000);
    }
    else if(Atk == AtaqueActivo::ATK5){
        NumVar=0;
        Ataque6(*this);
        Atk = AtaqueActivo::ATK6;
        AtkDuration->start(13000);
        AtkDelay->start(16000);

    }
    else if(Atk == AtaqueActivo::ATK6){
        Atk = AtaqueActivo::Ninguno;
        ClearAll();
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

//____________________________________CLEAR ALL____________________________________//

void UnderTale::ClearAll(){
    AtkDuration->stop();
    AtkDelay->stop();
    Reproductor->stop();
    if (BackGround->scene() != nullptr) Escena->removeItem(BackGround);
    if (Jugador->scene() != nullptr) Escena->removeItem(Jugador);
    Jugador->removeHealthBar();
    if (Caja->scene() != nullptr) Escena->removeItem(Caja);
    disconnect(AtkConnection);
    disconnect(OtherConnection);
    disconnect(Reproducir, &QPushButton::clicked,this,&UnderTale::StartGame);
    disconnect(AtkDuration, &QTimer::timeout, this, &UnderTale::AttackPattern);
}
