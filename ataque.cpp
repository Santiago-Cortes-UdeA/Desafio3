#include "ataque.h"

Ataque::Ataque(Alma* alma, int x, int y, int damage_, QGraphicsScene *Escena): posx(x), posy(y), damage(damage_), jugador(alma), Escena(Escena), Check(new QTimer(this)) {
    connect (Check, &QTimer::timeout, this, &Ataque::Colision);
}

Ataque::~Ataque(){
    Check->stop();
}

void Ataque::Colision(){
    if(collidesWithItem(jugador)&&jugador->getVida()>0){
        jugador->BajarVida(damage);
    }
}
