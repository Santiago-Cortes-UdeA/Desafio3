#ifndef NIVEL_H
#define NIVEL_H

#include <QtMultimedia/QtMultimedia>
#include <QtMultimedia/QMediaPlayer>
#include <QGraphicsView>
#include <QLayout>

#include "alma.h"

class Nivel: public QGraphicsView
{
    Q_OBJECT
protected:
    Alma* Jugador;
    QMediaPlayer* Reproductor;
    QGraphicsPixmapItem* BackGround;
    QGraphicsScene* Escena;
    QGridLayout* Layout;
public:
    Nivel(QGraphicsScene*& Escena_, QString FileName, QGridLayout*& Layout_, QMediaPlayer*& Reproductor_);
protected:
    void keyPressEvent(QKeyEvent* event) override;
};

#endif // NIVEL_H
