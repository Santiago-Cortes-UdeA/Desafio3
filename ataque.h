#ifndef ATAQUE_H
#define ATAQUE_H
#include <QGraphicsPixmapItem>
#include "QObject"
#include <Qdebug>
#include "alma.h"
#include <QTimer>

class Ataque:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ataque(Alma* alma, int x, int y, int damage_, QGraphicsScene* Escena);
    ~Ataque();
protected:
    int posx;
    int posy;
    int damage;
    Alma* jugador;
    QTimer* Check;
    QGraphicsScene* Escena;
protected slots:
    virtual void Colision();
};

#endif // ATAQUE_H
