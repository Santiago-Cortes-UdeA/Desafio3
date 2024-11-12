#include "ataque.h"

Ataque::Ataque(Alma* alma, int x, int y, int damage_, QGraphicsScene *Escena, bool Azul_): posx(x), posy(y), damage(damage_), jugador(alma), Escena(Escena), Check(new QTimer(this)), Azul(Azul_) {
    connect (Check, &QTimer::timeout, this, &Ataque::Colision);
}

Ataque::~Ataque(){
    Check->stop();
}

void Ataque::Colision(){
    if(collidesWithItem(jugador)&&jugador->getVida()>0){
        if (!Azul)
            jugador->BajarVida(damage);

        else if (jugador->isMoving())
            jugador->BajarVida(damage);
    }
}
