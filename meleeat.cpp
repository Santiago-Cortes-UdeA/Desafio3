#include "meleeat.h"


MeleeAT::MeleeAT(Alma* alma, int x, int y, int damage, QGraphicsScene* Escena_, QString SpriteFileName, bool Azul_, int CantMov, int TMov, int DirMov):Ataque(alma, x, y, damage, Escena_, Azul_), CantMovimiento(CantMov), TiempoMov(TMov), DireccionMovimiento(DirMov), Desplazamiento (new QTimer(this)){
    QPixmap Sprite (SpriteFileName);
    if (!Azul){
        setPixmap(Sprite.copy(0,0,(Sprite.width()/2)-2,Sprite.height()));
    }
    else{
        setPixmap(Sprite.copy(Sprite.width()/2,0,(Sprite.width()/2)-2,Sprite.height()));
    }
    setScale(0.25);
    if (CantMovimiento!=0 && TiempoMov>0){
        ConexionMov = connect (Desplazamiento, &QTimer::timeout, this, &MeleeAT::Movimiento);
        Desplazamiento->start(TiempoMov);
    }
    connect(jugador, &Player::gameOver, this, &MeleeAT::RemoveFromScene);
    AddToScene();
}

void MeleeAT::AddToScene(){
    setPos(posx,posy);
    Escena->addItem(this);
    Check->start(100);
}

void MeleeAT::RemoveFromScene(){
    disconnect(jugador, &Player::gameOver, this, &MeleeAT::RemoveFromScene);
    if (ConexionMov) disconnect(ConexionMov);
    Escena->removeItem(this);
    Check->stop();
    delete(this);
}

void MeleeAT::Movimiento(){
    posx+=CantMovimiento*qCos(qDegreesToRadians(DireccionMovimiento));
    posy-=CantMovimiento*qSin(qDegreesToRadians(DireccionMovimiento));
    setPos(posx,posy);
    if (posx<390||posx>890||posy<250||posy>570){
        RemoveFromScene();
    }
}
