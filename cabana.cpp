#include "cabana.h"
#include <QDebug>


Cabana::Cabana(int cantvidas, QGraphicsScene *Escena)
    : vidas(cantvidas), posx(595), posy(260), ancho(90), alto(85),
    SpriteSheet("cabanaorg.png"), dxD(0), dxI(0), Mover(new QTimer(this)), inmunidadTimer(new QTimer(this)), inmunidad(false), Escena(Escena) {

    if (!SpriteSheet.isNull()) {
        setPixmap(QPixmap(SpriteSheet.copy(0,0,ancho,alto)));
        setScale(1.2);
    } else {
        qDebug() << "Error: SpriteSheet not loaded.";
    }

    setPos(posx, posy);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    inmunidadTimer->setSingleShot(true);
    connect(Mover, &QTimer::timeout, this, &Cabana::Movimiento);
    connect(inmunidadTimer, &QTimer::timeout, this, &Cabana::finInmunidad);


    actualizarVidas();
}

void Cabana::keyPressEvent(QKeyEvent* event){

    if (event->key() == Qt::Key_A) dxI = -5;

    if (event->key() == Qt::Key_D) dxD = 5;

    if (!Mover->isActive()) Mover->start(50);
}

void Cabana::keyReleaseEvent(QKeyEvent *event){
    if (event->isAutoRepeat()) return;

    switch (event->key()) {

    case Qt::Key_A: dxI = 0; break;

    case Qt::Key_D: dxD = 0; break;
    }

    if (dxD == 0 && dxI == 0 && Mover->isActive()) {
        Mover->stop();
    }
}

void Cabana::Movimiento(){
    posx+=dxD+dxI;
    if (posx < 815 && posx > 360) {
        setPos(posx, posy);
    }
    else {
        posx -= dxI + dxD;
    }



}

void Cabana::actualizarVidas(){

    if (vidasImagen) {
        Escena->removeItem(vidasImagen);
        delete vidasImagen;
    }

    QPixmap spriteVidas("vidas.png");

    if (spriteVidas.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen de las vidas.";
        return;
    }


    int subimagenAlto = 42;
    int posY = (3 - vidas)* subimagenAlto;

    QPixmap subimagenVidas = spriteVidas.copy(0, posY, 137, subimagenAlto);


    vidasImagen = new QGraphicsPixmapItem(subimagenVidas);

    int offsetY = 15;
    vidasImagen->setPos(800, 610);
    Escena->addItem(vidasImagen);
}

void Cabana::PerderVida(){
    if (inmunidad) return;
    inmunidad = true;
    vidas -= 1;
    qDebug() << "Vidas restantes:" << vidas;
    inmunidadTimer->start(2000);
    actualizarVidas();
}

void Cabana::finInmunidad() {
    inmunidad = false;
}
