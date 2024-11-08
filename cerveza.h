#ifndef CERVEZA_H
#define CERVEZA_H
#include "ataque.h"
#include <QGraphicsRectItem>
#include "alma.h"
class Cerveza:public Ataque
{
    Q_OBJECT
public:
    Cerveza(Alma* alma, int x, int y, int damage_, QGraphicsScene *Escena, QTimer* Timer);
    void Remover();

private:
    int AlturaRelleno;
    QGraphicsRectItem* Relleno;
    QTimer* Subida;
    void Subir();
    QTimer* Quitar;

signals:
    void tope();
};

#endif // CERVEZA_H
