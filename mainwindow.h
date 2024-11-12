#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>

#include "undertale.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *Escena;
    QGraphicsView* Vista;

    QGridLayout* Layout;

    QGraphicsPixmapItem* Fondo;

    QPushButton* Nivel1;
    QGraphicsProxyWidget* Nivel1P;
    QPushButton* Nivel2;
    QGraphicsProxyWidget* Nivel2P;

    QMediaPlayer* Reproductor;
    QAudioOutput* AudioOutput;
    QGraphicsVideoItem* CutScene;

    QMetaObject::Connection ConnectionA;
    QMetaObject::Connection ConnectionB;

private slots:
    void LoadUTLevel();
    void MainMenu();
};
#endif // MAINWINDOW_H
