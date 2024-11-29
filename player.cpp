#include "player.h"

Player::Player(int MaxHP, QGraphicsScene *Scene, int x, int y)
    : VidaMax(MaxHP)
    , VidaActual(MaxHP)
    , Escena(Scene)
    , Mov(new QTimer())
    , IVF(new QTimer())
    , Invencible(false)
    , posx(x)
    , posy(y)
{}
