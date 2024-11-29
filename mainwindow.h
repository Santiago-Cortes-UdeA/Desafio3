#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QLabel>

#include "undertale.h"
#include "mountain.h"

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

    QVector<QPushButton*> Botones;
    QVector<QGraphicsProxyWidget*> BotonesP;

    QLabel* Info;
    QGraphicsProxyWidget* InfoP;

    QMediaPlayer* Reproductor;
    QAudioOutput* AudioOutput;
    QGraphicsVideoItem* CutScene;

    QMetaObject::Connection ConnectionA;
    QMetaObject::Connection ConnectionB;

    int Stats[6];

private slots:
    void LoadUTLevel();
    void LoadMountainLevel();
    void LoadAchievements();
    void MainMenu();
};
#endif // MAINWINDOW_H
