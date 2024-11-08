#include "burbuja.h"

Burbuja::Burbuja(Alma* alma, int x, int y, int damage, QGraphicsScene* Escena_, QString SpriteFileName, int CantMov, int TMov, int AnguloInicial):MeleeAT(alma, x, y, damage, Escena_, SpriteFileName, CantMov, TMov), Angulo(AnguloInicial) {
    setScale(0.75);
    if (ConexionMov){
        disconnect(ConexionMov);
        ConexionMov=connect(Desplazamiento, &QTimer::timeout, this, &Burbuja::Movimiento);
    }
}

void Burbuja::Movimiento(){
    posx+=5*qSin(qDegreesToRadians(Angulo));
    posy-=CantMovimiento;
    setPos(posx,posy);
    if (posy<300){
        RemoveFromScene();
    }
    Angulo+=10;
}
