#ifndef NIVEL_H
#define NIVEL_H

#include <QtMultimedia/QtMultimedia>
#include <QtMultimedia/QMediaPlayer>
#include <QObject>
#include <QLayout>

#include "alma.h"

class Nivel: public QObject
{
    Q_OBJECT
protected:
    Alma* Jugador;
    QMediaPlayer* Reproductor;
    QAudioOutput* AudioOutput;
    QGraphicsPixmapItem* BackGround;
    QGraphicsScene* Escena;
    QGridLayout* Layout;
public:
    Nivel(QGraphicsScene*& Escena_, QString FileName, QGridLayout*& Layout_);
};

#endif // NIVEL_H
