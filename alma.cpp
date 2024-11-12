#include "alma.h"

Alma::Alma(QGraphicsScene *Escena_):posx(445),posy(445),vidamax(20), Invencible(false), Escena(Escena_), Mov(new QTimer(this)), dxR(0), dyU(0), dxL(0), dyD(0), Azul(false) {
    QPixmap pixmap("Alma.png");
    setPixmap(pixmap);
    setPos(posx,posy);
    vida=vidamax;

    qDebug()<<posx<<" "<<pos().x();

    setFlag(QGraphicsItem::ItemIsFocusable);

    IVF.setSingleShot(true);
    connect(&IVF, &QTimer::timeout, this, &Alma::Vulnerable);

    HealthBar = new QGraphicsRectItem;
    HealthBar->setRect(550,650,200,35);
    HealthBar->setBrush(QBrush(Qt::yellow));

    HealthBox = new QGraphicsRectItem;
    HealthBox->setRect(550,650,200,35);
    HealthBox->setBrush(QBrush(Qt::red));

    InfoAlma = new QGraphicsTextItem;
    InfoJugador = new QGraphicsTextItem;
    QString Info = QString("%1 / %2")
                       .arg(vida)
                       .arg(vidamax);
    InfoAlma->setFont(QFont("Mars Needs Cunnilingus", 25));
    InfoJugador->setFont(QFont("Mars Needs Cunnilingus", 25));
    InfoAlma->setPlainText(Info);
    InfoJugador->setPlainText(QString("Sr.Burns  LV 1    HP"));

    connect(Mov, &QTimer::timeout, this, &Alma::movimiento);
}

//____________________________________MOVEMENT____________________________________//

void Alma :: keyPressEvent(QKeyEvent *event){
    qDebug()<<"Key Press in Alma";
    if (vida>0){
        switch (event->key()){
        case Qt::Key_Up:
            if (!Azul){
                dyU=-5;
            }
            else{
                if (posy==570){
                    dyU=-18;
                }
            }
            break;
        case Qt::Key_Down:
            if (!Azul)
                dyD=5;
            break;
        case Qt::Key_Left:
            dxL=-5;
            break;
        case Qt::Key_Right:
            dxR=5;
            break;
        }

        if (!Mov->isActive()){
            Mov->start(40);
        }
    }
}

void Alma :: keyReleaseEvent(QKeyEvent *event){
    if (event->isAutoRepeat()) return;
    switch (event->key()) {
        case Qt::Key_Up:
            if (!Azul)
                dyU=0;
            else{
                if (dyD==0){
                    dyU=0;
                }
            }
            break;
        case Qt::Key_Down:
            if (!Azul)
                dyD=0;
            break;
        case Qt::Key_Left:
            dxL=0;
            break;
        case Qt::Key_Right:
            dxR = 0;
            break;
        }

    if (!Azul && dxR==0 && dyU==0 && dxL==0 && dyD==0 && Mov->isActive()){
        Mov->stop();
    }
}

void Alma::movimiento(){
    if ((dxR>0 && posx+30<890) || (dxL<0 && posx-5>390)){
        posx+=dxR+dxL;
    }
    if (!Azul){

        if ((dyD>0 && posy+30<600) || (dyU<0 && posy-5>300)){
                posy+=dyD+dyU;
            }
        }
        else{

            if (dyU==0&&posy+30<600){
                dyD+=1;
            }
            else if (dyD==0&&dyU<0){
                dyU+=1;
            }
            posy+=dyD+dyU;
            if (posy+30>=600){
                posy=570;
                dyD=0;
            }
        }


    setPos(posx,posy);
}

void Alma::MoveToCenter(){
    if(posx>630){
        setPos(posx-=5,posy);
        qDebug()<<"Move x";
    }
    else if(posx<630){
        setPos(posx+=5, posy);
        qDebug()<<"Move x";
    }

    if(posy>445){
        setPos(posx, posy-=5);
        qDebug()<<"Move y";
    }
    else if(posy<445){
        setPos(posx, posy+=5);
        qDebug()<<"Move y";
    }

    if ((posx > 620 && posx < 640) && (posy > 435 && posy<455)){
        emit Center();
    }
}

bool Alma::isMoving(){
    if (dxR==0 && dxL==0 && dyU==0 && dyD==0){
        return false;
    }
    return true;
}

//____________________________________SOUL SETTERS____________________________________//

void Alma::Reset(){
    setFocus();
    posx=630;
    posy=445;
    dxR=0;
    dxL=0;
    dyU=0;
    dyD=0;
    setPos(posx,posy);
    vida=vidamax;
    HealthBar->setRect(550,650,200,35);
    setPixmap(QPixmap("Alma.png"));
    QString Info = QString("%1 / %2")
                       .arg(vida)
                       .arg(vidamax);
    InfoAlma->setPlainText(Info);
}

void Alma::BajarVida(int damage){
    if (Invencible) return;
    vida-=damage;
    if (vida>0){
        setPixmap(QPixmap("AlmaInv.png"));
        Invencible = true;
        qDebug()<<"Vida actual: "<<vida;
        IVF.start(1000);
        setHealthBar();
    }
    else{
        if(Mov->isActive()){
            Mov->stop();
        }
        if (Azul){
            changeSoulMode();
        }
        vida = 0;
        setHealthBar();
        setPixmap(QPixmap("Dead.png"));
        dxR=0;
        dxL=0;
        dyU=0;
        dyD=0;
        emit gameOver();
    }
}

void Alma::Vulnerable(){
    Invencible=false;
    if (!Azul)
        setPixmap(QPixmap("Alma.png"));
    else
        setPixmap(QPixmap("AlmaB.png"));
}

void Alma::changeSoulMode(){
    Azul=!Azul;
    dyU=0;
    dyD=0;
    if (Azul){
        setPixmap(QPixmap("AlmaB.png"));
        if (!Mov->isActive()){
            dyD=-1;
            Mov->start(40);
        }
    }
    else{
        setPixmap(QPixmap("Alma.png"));
    }
}
//____________________________________HEALTH BAR____________________________________//

void Alma::setHealthBar(){
    qreal largo = (qreal(vida)/vidamax)*200;
    HealthBar->setRect(550,650,largo,35);
    QString Info = QString("%1 / %2")
                       .arg(vida)
                       .arg(vidamax);
    InfoAlma->setPlainText(Info);
}

void Alma::addHealthBar(){
    Escena->addItem(HealthBox);
    Escena->addItem(HealthBar);
    InfoJugador->setPos(180,650);
    InfoAlma->setPos(780,650);
    Escena->addItem(InfoJugador);
    Escena->addItem(InfoAlma);
}

void Alma::removeHealthBar(){
    if (HealthBox->scene() != nullptr) Escena->removeItem(HealthBox);
    if (HealthBar->scene() != nullptr) Escena->removeItem(HealthBar);
    if (InfoJugador->scene() != nullptr) Escena->removeItem(InfoJugador);
    if (InfoAlma->scene() != nullptr) Escena->removeItem(InfoAlma);
}


