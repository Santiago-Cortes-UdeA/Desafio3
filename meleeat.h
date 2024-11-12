#ifndef MELEEAT_H
#define MELEEAT_H
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "QObject"
#include <Qdebug>
#include "ataque.h"
#include "alma.h"
#include <QTimer>
#include <QMetaObject>
class MeleeAT:public Ataque
{
    Q_OBJECT
public:
    MeleeAT(Alma* alma, int x, int y, int damage, QGraphicsScene* Escena_, QString SpriteFileName, bool Azul_ = false, int CantMov = 0, int TMov = 0, int DirMov = 0);
    void AddToScene();
    void RemoveFromScene();

protected:
    int CantMovimiento;
    int TiempoMov;
    int DireccionMovimiento;
    QTimer* Desplazamiento;
    QMetaObject::Connection ConexionMov;

protected slots:
    void Movimiento();
};

#endif // MELEEAT_H
