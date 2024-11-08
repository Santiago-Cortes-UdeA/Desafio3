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
    UnderTale(QGridLayout*& Layout, QGraphicsScene*& Escena, QString FileName);
    ~UnderTale();

    friend void Ataque1(UnderTale& UT);
    friend void Ataque2(UnderTale& UT);
    friend void Ataque3(UnderTale& UT);
    qreal Angulo;
    friend void Ataque4(UnderTale& UT);
    friend void StopSpawn(UnderTale& UT);

    enum class AtaqueActivo {Ninguno, ATK1, ATK2, ATK3, ATK4};
    AtaqueActivo Atk;

private:
    QGraphicsVideoItem* CutScene;
    QGraphicsRectItem* Caja;
    QTimer* AtkDuration;
    QTimer* Spawn;
    QMetaObject::Connection AtkConnection;
    QMetaObject::Connection OtherConnection;

    //Para debugging
    QPushButton* Reproducir;

private slots:
    void StartGame();
    void StopGame();

    void GameOver();
    void GameOverTransition();
    void GameOverMenu();

    void generarBlaster();
    void lluviaDeDonas();
    void DuffRound(qreal& Angulo);
    void Burbujas();
    void AttackPattern();

signals:
    void ReturnToMainMenu();
};

#endif // UNDERTALE_H
