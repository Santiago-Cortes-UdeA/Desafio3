#include "obstaculos.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QDebug>

Obstaculos::Obstaculos(QGraphicsScene* escena, Cabana* Casa)
    : posx(QRandomGenerator::global()->bounded(360, 815)),  // Posición aleatoria en X
    ancho(124), // Ancho del obstáculo
    alto(90), // Alto base del obstáculo
    Jugador(Casa) // Referencia al jugador
{
    // Cargar la hoja de sprite con los obstáculos
    SpriteSheet = QPixmap("obstaculos.png");

    // Verificar si la imagen se ha cargado correctamente
    if (SpriteSheet.isNull()) {
        qDebug() << "Error: No se pudo cargar obstaculos.png";
        return;  // Salimos si no se carga correctamente
    }

    // Elegir aleatoriamente una fila y columna para la subimagen
    int fila = QRandomGenerator::global()->bounded(3);  // Elegir fila aleatoria (0, 1, 2)
    int columna = QRandomGenerator::global()->bounded(3);  // Elegir columna aleatoria (0, 1, 2)

    // Ajustar el alto según la fila seleccionada
    if (fila == 0) {
        alto = 90;   // Primer obstáculo
    } else if (fila == 1) {
        alto = 242;  // Segundo obstáculo
    } else if (fila == 2) {
        alto = 380;  // Tercer obstáculo
    }

    if (ancho <= 300 && alto <= 300) {

        setPixmap(SpriteSheet.copy(columna * ancho, fila * alto, ancho, alto));
    } else {
        qDebug() << "Error: Se intentó copiar una subimagen de tamaño mayor a 400x400";
    }


    posy= 600-alto;
    setPos(posx, posy);
    escena->addItem(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Obstaculos::mover);
    timer->start(50);  // Mover cada 50 ms
}

void Obstaculos::mover()
{
    posy -= 5;
    setPos(posx, posy);

    if (collidesWithItem(Jugador)){
        Jugador->PerderVida();
        scene()->removeItem(this);
        delete this;
    }

    else if (posy <= 200) {
        scene()->removeItem(this);
        delete this;
    }
}
