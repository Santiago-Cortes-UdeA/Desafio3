#include "nivel.h"

Nivel::Nivel(QGraphicsScene *&Escena_, QString FileName, QGridLayout*& Layout_):Jugador(new Alma(Escena_)), Reproductor(new QMediaPlayer), AudioOutput(new QAudioOutput), Escena(Escena_), BackGround(new QGraphicsPixmapItem(FileName)), Layout(Layout_) {}
