#ifndef OBSTACULOS_H
#define OBSTACULOS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "cabana.h"

class Obstaculos : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Obstaculos(QGraphicsScene* escena, Cabana* Casa);
    void mover();

    int tipo() const { return Type; }

private:
    QPixmap SpriteSheet;
    Cabana* Jugador;
    int posx;
    int posy;
    int ancho;
    int alto;
    QTimer* timer;

    static const int Type = QGraphicsItem::UserType + 1;
};

#endif // OBSTACULOS_H
