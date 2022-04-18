#include "player.h"
#include "ui_player.h"
#include "song.h"
#include "list.h"
#include <QMediaPlayer>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <QVariant>

int rows(0);
player::player(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::player)
{
    ui->setupUi(this);
    ///Table
    table = new QTableWidget();
    ui->Table->addWidget(table);
//    QString styleSheetTable = "background:#444444";
//  table->setStyleSheet(styleSheetTable);


    ///List
    myList = new list();
    myList->setTable(table);
    table->setMinimumWidth(1250);
    table->setColumnWidth(2,600);
    table->setSortingEnabled(true);

    /// PrgBar Connections
    mMediaPlayer = new QMediaPlayer(this);

    connect(mMediaPlayer, &QMediaPlayer::positionChanged, [&] (qint64 pos) {
        ui->prgBar->setValue(pos) ;
    });

    connect (mMediaPlayer, &QMediaPlayer:: durationChanged, [&] (qint64 dur) {
        ui->prgBar->setMaximum(dur);
    });

    /*if(myList->isEmpty())
        ui->btnPlay->setEnabled(false);
    else{
        ui->btnPlay->setEnabled(true);
    }*/
}

player::~player()
{
    delete ui;
}


void player::on_btnAdd_clicked()
{

    song mySong;
    QString name ,author,address;
    name = ui->txtName->text();
    author = ui->txtAutor->text();
    address = ui->lblAddress->text();

    mySong.setName(name);
    mySong.setAuthor(author);
    mySong.setAddress(address);

    myList->insertElem(nullptr,mySong);

    ui->txtName->clear();
    ui->txtAutor->clear();
    ui->lblAddress->clear();
    ui->lblAddress->setText("URL");

     ui->lblActualSong->setText(myList->getCurrentSong().getName());

   /* if(myList->isEmpty())
        ui->btnPlay->setEnabled(false);
    else{
        ui->btnPlay->setEnabled(true);
    }*/


}


void player::on_btnSelect_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Selecciona una cancion");
    if (filename.isEmpty()) {
        return;
    }

    ui->lblAddress->setText(filename);

}


void player::on_btnPlay_clicked()
{
    if(ui->prgBar->value() == 0){
    QString address =  myList->getCurrentSong().getAddress();
    mMediaPlayer->setMedia(QUrl::fromLocalFile(address));
    mMediaPlayer->setVolume(ui->sldVolume->value());}

    mMediaPlayer->play();


}


void player::on_btnNext_clicked()
{
    mMediaPlayer->stop();
    myList->nextSong();
    ui->lblActualSong->setText(myList->getCurrentSong().getName());



}

void player::on_btnPrev_clicked()
{
    mMediaPlayer->stop();
    myList->prevSong();
     ui->lblActualSong->setText(myList->getCurrentSong().getName());
}


void player::on_btnPause_clicked()
{
    mMediaPlayer->pause();
}

void player::on_btnStop_clicked()
{
    mMediaPlayer->stop();
}


void player::on_btnDelete_clicked()
{
    /*rows--;
    ///Eliminar al principio
    table->removeRow(0);*/
    myList->deleteFirstElem();

    ///Eliminar al final
    //table->removeRow(rows);


}


void player::on_btnReverse_clicked()
{
   /// int i = table->currentRow();

   ///8 ui->lblName->setText(QString::number(i));
    myList->reverse();
}


void player::on_sldVolume_valueChanged(int value)
{
    mMediaPlayer->setVolume(value);
}


void player::on_btnMute_clicked()
{
    if (ui->btnMute->text() == "Mute"){
      mMediaPlayer->setMuted(true);
      ui->btnMute->setText ("Unmute");
    } else {
      mMediaPlayer->setMuted (false);
       ui->btnMute->setText ("Mute");
    }

}

