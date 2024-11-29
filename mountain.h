#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#include "nivel.h"
#include "cabana.h"
#include "obstaculos.h"

#include <QGraphicsScene>
#include <QGraphicsTextItem>

class Mountain:public Nivel
{
public:
    Mountain(QGraphicsScene*& Escena_, QString FileName, QMediaPlayer*& Reproductor_);

private:
    Cabana* Jugador;
    QGraphicsTextItem* TiempoTexto;
    QTimer* temporizador;
    int tiempoRestante;
};

#endif // MOUNTAIN_H
