#ifndef BURBUJA_H
#define BURBUJA_H
#include "meleeat.h"

class Burbuja:public MeleeAT
{
public:
    Burbuja(Alma* alma, int x, int y, int damage, QGraphicsScene* Escena_, QString SpriteFileName, int CantMov=0, int TMov=0, int AnguloInicial=0);

private:
    qreal Angulo;

private slots:
    void Movimiento();
};

#endif // BURBUJA_H
