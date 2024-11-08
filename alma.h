#ifndef ALMA_H
#define ALMA_H
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include "QObject"
#include <Qdebug>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class Alma:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Alma(QGraphicsScene* Escena_);
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void Reset();
    void BajarVida(int damage);
    void Invulnerable();
    int getVida(){return vida;}
    int getx(){return posx;}
    int gety(){return posy;}
    void setHealthBar();
    void addHealthBar();
    void removeHealthBar();

private:
    QGraphicsPixmapItem* alma;
    int posx;
    int posy;
    int vida;
    int vidamax;
    bool Invencible;
    QTimer IVF;
    QGraphicsRectItem* HealthBar;
    QGraphicsRectItem* HealthBox;
    QGraphicsScene* Escena;
    QGraphicsTextItem* InfoJugador;
    QGraphicsTextItem* InfoAlma;
    QTimer* Mov;
    int dxR;
    int dxL;
    int dyU;
    int dyD;
private slots:
    void Vulnerable();
    void movimiento();
public slots:
    void MoveToCenter();
signals:
    void gameOver();
    void Center();
};

#endif // ALMA_H
