#include "nivel.h"

Nivel::Nivel(QGraphicsScene *&Escena_, QString FileName, QMediaPlayer*& Reproductor_)
    : player(nullptr)
    , Reproductor(Reproductor_)
    , Escena(Escena_)
    , BackGround(new QGraphicsPixmapItem(FileName))

    {}
