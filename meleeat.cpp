#include "meleeat.h"


MeleeAT::MeleeAT(Alma* alma, int x, int y, int damage, QGraphicsScene* Escena_, QString SpriteFileName, int CantMov, int TMov, int DirMov):Ataque(alma, x, y, damage, Escena_), CantMovimiento(CantMov), TiempoMov(TMov), DireccionMovimiento(DirMov), Desplazamiento (new QTimer(this)){
    setPixmap(QPixmap(SpriteFileName));
    setScale(0.25);
    if (CantMovimiento!=0 && TiempoMov>0){
        ConexionMov = connect (Desplazamiento, &QTimer::timeout, this, &MeleeAT::Movimiento);
        Desplazamiento->start(TiempoMov);
    }
    connect(jugador, &Alma::gameOver, this, &MeleeAT::RemoveFromScene);
    AddToScene();
}

void MeleeAT::AddToScene(){
    setPos(posx,posy);
    Escena->addItem(this);
    Check->start(100);
}

void MeleeAT::RemoveFromScene(){
    disconnect(jugador, &Alma::gameOver, this, &MeleeAT::RemoveFromScene);
    if (ConexionMov) disconnect(ConexionMov);
    Escena->removeItem(this);
    Check->stop();
    delete(this);
}

void MeleeAT::Movimiento(){
    posx+=CantMovimiento*qCos(qDegreesToRadians(DireccionMovimiento));
    posy-=CantMovimiento*qSin(qDegreesToRadians(DireccionMovimiento));
    setPos(posx,posy);
    if (posx<0||posx>890||posy<0||posy>570){
        RemoveFromScene();
    }
}
