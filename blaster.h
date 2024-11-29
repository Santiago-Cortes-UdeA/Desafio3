#ifndef BLASTER_H
#define BLASTER_H
#include <QGraphicsPixmapItem>
#include "QObject"
#include <QTimer>
#include <QGraphicsScene>
#include <QMetaObject>
#include "alma.h"
#include "player.h"
#include "ataque.h"

class Blaster:public Ataque
{
    Q_OBJECT
public:
    Blaster(Alma* alma, QGraphicsScene* Escena, int x, int y, qreal orientacion_);

private:
    QGraphicsPixmapItem* Duff;
    QGraphicsRectItem* Laser;
    QTimer* Delay;
    int orientacion;

private slots:
    void Disparar();
    void Colision() override;
    void Desaparecer();
};

#endif // BLASTER_H
