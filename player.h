#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QTableWidget>
#include "song.h"
#include "list.h"
QT_BEGIN_NAMESPACE
namespace Ui { class player; }
QT_END_NAMESPACE
class QMediaPlayer;
class list;
class player : public QMainWindow
{
    Q_OBJECT

public:
    player(QWidget *parent = nullptr);
    ~player();

private slots:
    void on_btnAdd_clicked();

    void on_btnSelect_clicked();

    void on_btnPlay_clicked();

    void on_btnPause_clicked();

    void on_btnNext_clicked();

    void on_btnPrev_clicked();

    void on_btnStop_clicked();

    void on_btnDelete_clicked();

    void on_btnReverse_clicked();

    void on_sldVolume_valueChanged(int value);

    void on_btnMute_clicked();

private:
    Ui::player *ui;
    QMediaPlayer *mMediaPlayer;
    QTableWidget *table;
    list *myList;

};
#endif // PLAYER_H
