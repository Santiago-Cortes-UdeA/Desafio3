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

class UnderTale:public Nivel
{
    Q_OBJECT
public:
    UnderTale(QGridLayout*& Layout, QGraphicsScene*& Escena, QString FileName, QMediaPlayer*& Reproductor_);
    ~UnderTale();

    friend void Ataque1(UnderTale& UT);
    friend void Ataque2(UnderTale& UT);
    friend void Ataque3(UnderTale& UT);
    qreal NumVar;
    friend void Ataque4(UnderTale& UT);
    friend void Ataque5(UnderTale& UT);
    friend void Ataque6(UnderTale& UT);

    enum class AtaqueActivo {Ninguno, ATK1, ATK2, ATK3, ATK4, ATK5, ATK6};
    AtaqueActivo Atk;

private:
    QGraphicsRectItem* Caja;
    QTimer* AtkDuration;
    QTimer*AtkDelay;
    QTimer* Spawn;
    QGraphicsTextItem* GAMEOVER;

    QMetaObject::Connection AtkConnection;
    QMetaObject::Connection OtherConnection;

    QPushButton* Reproducir;

    QVector<QGraphicsProxyWidget*> BotonesP;

    void ClearAll();
private slots:
    void StartGame();

    void GameOver();
    void GameOverTransition();
    void GameOverMenu();

    void generarBlaster();
    void lluviaDeDonas();
    void DuffRound(qreal& Angulo);
    void Burbujas();
    void BeerJump();
    void BlueBeer(qreal& SpawnedNumber);
    void AttackPattern();

    void StopSpawn();

signals:
    void ReturnToMainMenu();
};

#endif // UNDERTALE_H
