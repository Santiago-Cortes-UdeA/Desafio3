#ifndef CABANA_H
#define CABANA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>


class Cabana:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Cabana(int cantvidas, QGraphicsScene* Escena);
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void PerderVida();

private:
    int vidas;
    qreal posx;
    qreal posy;
    int ancho;
    int alto;
    QPixmap SpriteSheet;
    qreal dxD;
    qreal dxI;
    QTimer* Mover;

    QTimer* inmunidadTimer;
    bool inmunidad;


    QGraphicsPixmapItem* vidasImagen = nullptr;
    QGraphicsScene* Escena;

private slots:
    void Movimiento();
    void finInmunidad();

public slots:
    void actualizarVidas();
};

#endif // CABANA_H


