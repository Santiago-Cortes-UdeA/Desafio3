#ifndef UNDERTALE_H
#define UNDERTALE_H

#include <QMediaPlayer>
#include <QtMultimediaWidgets/QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QUrl>
#include <QAudioOutput>
#include <QGraphicsRectItem>
#include <QPen>
#include <QTimer>
#include <QMetaObject>
#include <QPushButton>
#include <QLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>

#include "nivel.h"
#include "alma.h"
#include "meleeat.h"
#include "blaster.h"
#include "burbuja.h"
#include "cerveza.h"
#include "player.h"

class UnderTale:public Nivel
{
    Q_OBJECT
public:
    UnderTale(QGraphicsScene*& Escena, QString FileName, QMediaPlayer*& Reproductor_, int playerHP);
    ~UnderTale();

    qreal NumVar;
    friend void Ataque1(UnderTale& UT);
    friend void Ataque2(UnderTale& UT);
    friend void Ataque3(UnderTale& UT);
    friend void Ataque4(UnderTale& UT);
    friend void Ataque5(UnderTale& UT);
    friend void Ataque6(UnderTale& UT);
    friend void Ataque7(UnderTale& UT);
    friend void Ataque8(UnderTale& UT);
    friend void Ataque9(UnderTale& UT);
    friend void EndingCutScene(UnderTale& UT);
    friend void AtaqueFinal(UnderTale& UT);

    enum class AtaqueActivo {Ninguno, ATK1, ATK2, ATK3, ATK4, ATK5, ATK6, ATK7, ATK8, ATK9, ATKFINAL, EndCutscene};
    AtaqueActivo Atk;

private:
    Alma* Jugador;

    QGraphicsRectItem* Caja;
    QTimer* AtkDuration;
    QTimer*AtkDelay;
    QTimer* Spawn;
    QGraphicsTextItem* GAMEOVER;

    QMetaObject::Connection AtkConnection;
    QMetaObject::Connection OtherConnection;

    QPushButton* Reproducir;

    QVector<QGraphicsProxyWidget*> BotonesP;

    QGraphicsPixmapItem* Luchar;

    void ClearAll();
private slots:
    void StartGame();

    void GameOver();
    void GameOverTransition();
    void GameOverMenu();

    void generarBlaster();
    void lluviaDeDonas();
    void DuffRound();
    void Burbujas();
    void BeerJump();
    void BlueBeer();
    void SmallJump();
    void DonutBlaster();
    void BottleCircling();
    void RandomJumps();
    void MoveFightButton();
    void AttackPattern();

    void StopSpawn();

signals:
    void ReturnToMainMenu();
};

#endif // UNDERTALE_H
