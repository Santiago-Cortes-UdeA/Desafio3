#include "blaster.h"
#include <QtMath>
Blaster::Blaster(Alma* alma, QGraphicsScene* Escena, int x, int y, qreal orientacion_=0): Ataque(alma, x, y, 5, Escena), orientacion(orientacion_), Laser(nullptr) {
    Duff = new QGraphicsPixmapItem(QPixmap("Duff.png"), this);
    setPos(posx,posy);
    setRotation(orientacion);
    Delay = new QTimer(this);
    Delay->setSingleShot(true);
    Delay->start(1000);
    connect(Delay, &QTimer::timeout, this, &Blaster::Disparar);
    connect(jugador, &Alma::gameOver, this, &Blaster::Desaparecer);
    Escena->addItem(this);
}

void Blaster::Disparar(){
    Laser = new QGraphicsRectItem(0, 0, 50, 600);
    Laser->setBrush(Qt::white);
    Laser->setPos(posx+(45*qCos(qDegreesToRadians(rotation()))), posy+(45*qSin(qDegreesToRadians(rotation()))));
    Laser->setRotation(rotation()+180);
    Laser->setZValue(1);
    Escena->addItem(Laser);
    Check->start(100);
    connect(Check, &QTimer::timeout, this, &Blaster::Colision);
    Delay->stop();
    disconnect(Delay, &QTimer::timeout, this, &Blaster::Disparar);
    Delay->start(1000);
    connect(Delay, &QTimer::timeout, this, &Blaster::Desaparecer);
}

void Blaster::Colision(){
    if(Laser->collidesWithItem(jugador)&&jugador->getVida()>0){
        jugador->BajarVida(damage);
    }
}

void Blaster::Desaparecer(){
    disconnect(Check, &QTimer::timeout, this, &Blaster::Colision);
    disconnect(Delay, &QTimer::timeout, this, &Blaster::Desaparecer);
    disconnect(jugador, &Alma::gameOver, this, &Blaster::Desaparecer);
    Check->stop();
    Delay->stop();
    if (Laser){
        Escena->removeItem(Laser);
        delete Laser;
    }
    Escena->removeItem(this);
    delete this;
}
