#include "player.h"
#include "ui_player.h"
#include "song.h"
#include "list.h"
#include <QMediaPlayer>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <regex>
#include <string>
#include <QRegExpValidator>


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
    //table->setFixedWidth()
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

    ///Modify
    ui->spbxModify->setMinimum(1);
    ui->spbxModify->setMaximum(1);

    setEnableBtns(false);
}

player::~player()
{
    delete ui;
}

void player::setEnableBtns(bool value){
    ui->btnPrev->setEnabled(value);
    ui->btnPlay->setEnabled(value);
    ui->btnNext->setEnabled(value);
    ui->btnPause->setEnabled(value);
    ui->btnStop->setEnabled(value);
}

void player::on_btnAdd_clicked()
{
    /*const std::regex expReg("a");
    std::string expression = name.toStdString();
    if(std::regex_match(expression,expReg)){
        mySong.setAddress(address);
    }else{
        ui->lblName->setText("error");
        return;
    }*/

    song mySong;
    QString name ,author,address;
    name = ui->txtName->text();
    author = ui->txtAutor->text();
    address = ui->lblAddress->text();

    mySong.setName(name);
    mySong.setAuthor(author);
    mySong.setAddress(address);

    QRegExp rx("(.*\\.(wav|mp3))\$");
   QRegExpValidator* valiAddress=new QRegExpValidator(rx, this);
   if( !rx.exactMatch(ui->lblAddress->text()) || ui->txtName->text() == "" ||  ui->txtAutor->text() == ""){
        ///QDialog
       ui->txtName->clear();
       ui->txtAutor->clear();
       ui->lblAddress->clear();
       ui->lblAddress->setText("URL");
       return;
    }
    myList->insertElem(myList->getLastPos(),mySong);
    if(!myList->isEmpty())
        setEnableBtns(true);
    ui->txtName->clear();
    ui->txtAutor->clear();
    ui->lblAddress->clear();
    ui->lblAddress->setText("URL");

    ui->lblActualSong->setText(myList->getCurrentSong().getName());

    ui->spbxModify->setMaximum(myList->id);





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
    if(!myList->isEmpty()){
    myList->deleteLastElem();


    ///Eliminar al final
    //table->removeRow(rows);

      if(!myList->isEmpty()){
          mMediaPlayer->stop();
           ui->spbxModify->setMaximum(myList->id);
          ui->lblActualSong->setText(myList->getFirstPos()->data.getName());
      }
          else{
          mMediaPlayer->stop();
           setEnableBtns(false);
          ui->lblActualSong->setText("...");
      }
    }

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


   // table->selectRow(1);

}


void player::on_btnModify_clicked()
{
    int id=ui->spbxModify->value();
    song mySong;
    QString name ,author,address;
    name = ui->txtName->text();
    author = ui->txtAutor->text();
    address = ui->lblAddress->text();

    mySong.setName(name);
    mySong.setAuthor(author);
    mySong.setAddress(address);
     myList->modify(id,mySong);

    ui->txtName->clear();
    ui->txtAutor->clear();
    ui->lblAddress->clear();
    ui->lblAddress->setText("URL");

    table->selectRow(0);

}

