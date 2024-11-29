#ifndef ALMA_H
#define ALMA_H
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QObject>
#include <Qdebug>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "player.h"

class Alma:public Player
{
    Q_OBJECT
public:
    Alma(int MaxHP, QGraphicsScene* Escena_);

    void Reset();
    void BajarVida(int damage);
    void Invulnerable();
    void setHealthBar();
    void addHealthBar();
    void removeHealthBar();
    void changeSoulMode();
    bool isMoving();
    void stopSoul();

private:
    QGraphicsPixmapItem* alma;
    bool Azul;
    QGraphicsRectItem* HealthBar;
    QGraphicsRectItem* HealthBox;
    QGraphicsTextItem* InfoJugador;
    QGraphicsTextItem* InfoAlma;
    int dxR;
    int dxL;
    int dyU;
    int dyD;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void Vulnerable();
    void movimiento();
public slots:
    void MoveToCenter();
signals:
    void Center();
    void SoulMode();
};

#endif // ALMA_H
