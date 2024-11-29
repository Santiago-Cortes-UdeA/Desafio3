#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Player:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(int MaxHP, QGraphicsScene* Scene, int x, int y);
    int getVida(){return VidaActual;}
    int getx(){return posx;}
    int gety(){return posy;}

protected:
    int VidaMax;
    int VidaActual;
    bool Invencible;
    QTimer* IVF;
    QTimer* Mov;
    QGraphicsScene* Escena;
    int posx;
    int posy;


signals:
    void gameOver();
};

#endif // PLAYER_H
