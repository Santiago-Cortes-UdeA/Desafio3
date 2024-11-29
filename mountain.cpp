#include "mountain.h"

Mountain::Mountain(QGraphicsScene*& Escena_, QString FileName, QMediaPlayer*& Reproductor_)
    : Nivel(Escena_, FileName, Reproductor_)
    , tiempoRestante(120)
    , Jugador(new Cabana(3, Escena))
{
    QPixmap fondo(FileName);
    QBrush brush(fondo.scaled(1280, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    Escena->setBackgroundBrush(brush);

    QGraphicsRectItem* Caja = new QGraphicsRectItem();
    Caja->setRect(340,200,600,400);

    QPen Borde;
    Borde.setWidth(4);
    Borde.setBrush(QBrush(Qt::white));
    Caja->setPen(Borde);

    Escena->addItem(Caja);


    QGraphicsPixmapItem* fondoCaja = new QGraphicsPixmapItem(QPixmap("rectangulo.png").scaled(600, 400, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    fondoCaja->setPos(340, 200);
    Escena->addItem(fondoCaja);

    QGraphicsPixmapItem* relojItem = new QGraphicsPixmapItem(QPixmap("reloj.png").scaled(50, 50, Qt::KeepAspectRatio));
    relojItem->setPos(340, 610);  // Ubica la imagen del reloj
    Escena->addItem(relojItem);

    // Crear el QLabel para el temporizador
    TiempoTexto = new QGraphicsTextItem("2:00");
    TiempoTexto->setFont(QFont("Arial",28));
    TiempoTexto->setPos(400,600);
    Escena->addItem(TiempoTexto);

    // Crear el QTimer para el temporizador
    temporizador = new QTimer(this);
    connect(temporizador, &QTimer::timeout, this, [=]() {
        if (tiempoRestante > 0) {
            tiempoRestante--;
            int minutos = tiempoRestante / 60;
            int segundos = tiempoRestante % 60;
            QString Tiempo = QString("%1:%2")
                                 .arg(minutos)
                                 .arg(segundos>9 ? QString::number(segundos):"0"+QString::number(segundos));
            TiempoTexto->setPlainText(Tiempo);
        } else {
            temporizador->stop();  // Detener el temporizador cuando llegue a 00:00
        }
    });
    temporizador->start(1000);  // Actualizar cada segundo


    // Dentro de MainWindow::MainWindow
    QTimer *timerObstaculos = new QTimer(this);
    connect(timerObstaculos, &QTimer::timeout, this, [=]() {
        // Crear un nuevo obstáculo cada vez que el temporizador se active
        new Obstaculos(Escena, Jugador);  // 'Escena' es el puntero a la escena donde se agregan los objetos
    });
    timerObstaculos->start(2000);  // Crear un nuevo obstáculo cada 2 segundos

    Reproductor->setSource(QUrl("qrc:/Canciones/wel.mp3"));
    Reproductor->play();

    Escena->addItem(Jugador);
}
