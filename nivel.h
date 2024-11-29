#ifndef NIVEL_H
#define NIVEL_H

#include <QtMultimedia/QtMultimedia>
#include <QtMultimedia/QMediaPlayer>
#include <QGraphicsScene>

#include "player.h"

class Nivel: public QObject
{
    Q_OBJECT
protected:
    Player* player;
    QMediaPlayer* Reproductor;
    QGraphicsPixmapItem* BackGround;
    QGraphicsScene* Escena;
    void setPlayer(Player* jugador){player=jugador;}
public:
    Nivel(QGraphicsScene*& Escena_, QString FileName, QMediaPlayer*& Reproductor_);

    Player* getPlayerReference(){return player;}
};

#endif // NIVEL_H
