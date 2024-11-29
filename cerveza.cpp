#include "cerveza.h"

Cerveza::Cerveza(Alma* alma, int x, int y, int damage_, QGraphicsScene *Escena, QTimer* Timer):Ataque(alma,x,y,damage_,Escena), AlturaRelleno(0), Relleno(new QGraphicsRectItem), Subida (new QTimer(this)), Quitar(Timer) {
    setPixmap(QPixmap("Cerveza.png"));
    Relleno->setRect(posx,posy+35,500,AlturaRelleno);
    Relleno->setBrush(QBrush(Qt::white));
    Relleno->setPen(QPen(Qt::white));
    setPos(posx,posy);
    Escena->addItem(this);
    Escena->addItem(Relleno);
    Check->start(100);
    Subida->start(500);
    connect(Subida,&QTimer::timeout,this,&Cerveza::Subir);
    connect(Quitar, &QTimer::timeout, this, &Cerveza::Remover);
    connect(jugador, &Player::gameOver, this, &Cerveza::Remover);
    connect(Check, &QTimer::timeout, this, &Cerveza::CollisionRelleno);
}

void Cerveza::Subir(){
    if(posy>475){
        posy-=15;
        AlturaRelleno+=15;
        setPos(posx,posy);
        Relleno->setRect(posx,posy+35,500,AlturaRelleno);
    }
    else{
        emit tope();
        Subida->stop();
    }
}

void Cerveza::Remover(){
    disconnect(Check, &QTimer::timeout, this, &Cerveza::CollisionRelleno);
    disconnect(jugador, &Player::gameOver, this, &Cerveza::Remover);
    disconnect(Quitar, &QTimer::timeout, this, &Cerveza::Remover);
    Check->stop();
    Subida->stop();
    disconnect(Subida,&QTimer::timeout,this,&Cerveza::Subir);
    Escena->removeItem(Relleno);
    delete Relleno;
    Escena->removeItem(this);
    delete this;
}

void Cerveza::CollisionRelleno(){
    if(Relleno->collidesWithItem(jugador)&&jugador->getVida()>0){
            jugador->BajarVida(damage);
    }
}
