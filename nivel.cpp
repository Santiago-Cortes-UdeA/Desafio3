#include "nivel.h"

Nivel::Nivel(QGraphicsScene *&Escena_, QString FileName, QGridLayout*& Layout_, QMediaPlayer*& Reproductor_)
    : Jugador(new Alma(Escena_))
    , Reproductor(Reproductor_)
    , Escena(Escena_)
    , BackGround(new QGraphicsPixmapItem(FileName))
    , Layout(Layout_)
    {}

void Nivel::keyPressEvent(QKeyEvent* event)
{
    QGraphicsView::keyPressEvent(event);
}
