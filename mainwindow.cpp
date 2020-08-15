#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMediaPlaylist"
#include "QDir"
#include "QFileDialog"
#include "QIcon"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    system_init();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::system_init(){
    player=new QMediaPlayer(this);
    playlist=new QMediaPlaylist(this);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);

    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),
            this,SLOT(onStateChanged(QMediaPlayer::State)));
    connect(player,SIGNAL(positionChanged(qint64)),
            this,SLOT(onPositionChanged(qint64)));

    connect(player,SIGNAL(durationChanged(qint64)),
            this,SLOT(onDurationChanged(qint64)));
    connect(playlist,SIGNAL(currentIndexChanged(int)),
            this,SLOT(onPlaylistChanged(int)));


    ui->pushButton_4->setIcon(QIcon(":/image/music_start.ico"));
    ui->pushButton_5->setIcon(QIcon(":/image/music_pause.ico"));
    ui->pushButton_6->setIcon(QIcon(":/image/music_stop.ico"));
    ui->pushButton_7->setIcon(QIcon(":/image/music_last.ico"));
    ui->pushButton_8->setIcon(QIcon(":/image/music_next.ico"));
    ui->btn_silent->setIcon(QIcon(":/image/music_volume.ico"));
    //setWindowIcon(QIcon(":/image/start.png"));
}
void MainWindow::onStateChanged(QMediaPlayer::State state){
    ui->pushButton_4->setEnabled(!(state==QMediaPlayer::PlayingState));
    ui->pushButton_5->setEnabled(state==QMediaPlayer::PlayingState);
    ui->pushButton_6->setEnabled(state==QMediaPlayer::PlayingState);
}
void MainWindow::onPlaylistChanged(int position){
    ui->listWidget->setCurrentRow(position);
    QListWidgetItem *item=ui->listWidget->currentItem();
    if(item){
        ui->label_music->setText(item->text());
    }
}
void MainWindow::onDurationChanged(qint64 duration){
    ui->slider_time->setMaximum(int(duration));
    int secs=int(duration/1000);
    int mins=secs/60;
    secs=secs%60;
    durationtime=QString::asprintf("%d:%d",mins,secs);
    ui->label_time->setText(postiontime+"/"+durationtime);
}
void MainWindow::onPositionChanged(qint64 position){
    if(ui->slider_time->isSliderDown())
        return;
    ui->slider_time->setSliderPosition(int(position));
    int secs=int(position/1000);
    int mins=secs/60;
   postiontime=QString::asprintf("%d:%d",mins,secs);
    ui->label_time->setText(postiontime+"/"+durationtime);
}

void MainWindow::on_pushButton_clicked()
{
    QString curPath=QDir::homePath();
    QString dlgTitle="音乐播放器";
    QString filter="音频文件(*.mp3 *.wav *.wma);;mp3文件(*.mp3);;wav文件(*.wav);;wma文件(*.wma);;所有文件(*.*)";
    QStringList fileList=QFileDialog::getOpenFileNames(this,dlgTitle,curPath,filter);
    if(fileList.count()<1)
        return;
    for(int i=0;i<fileList.count();i++){
        QString aFile=fileList.at(i);
        playlist->addMedia(QUrl::fromLocalFile(aFile));
        QFileInfo fileInfo(aFile);
        ui->listWidget->addItem(fileInfo.fileName());
    }
    if(player->state()!=QMediaPlayer::PlayingState)
        playlist->setCurrentIndex(0);
    player->play();
}

void MainWindow::on_pushButton_2_clicked()
{
    int pos=ui->listWidget->currentRow();
    QListWidgetItem *item=ui->listWidget->takeItem(pos);
    delete item;
    playlist->removeMedia(pos);
}

void MainWindow::on_pushButton_3_clicked()
{
    playlist->clear();
    ui->listWidget->clear();
    player->stop();
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int rowNo=index.row();
    playlist->setCurrentIndex(rowNo);
    player->play();
}

void MainWindow::on_pushButton_4_clicked()
{
    if(playlist->currentIndex()<0)
        playlist->setCurrentIndex(0);
    player->play();
}

void MainWindow::on_pushButton_5_clicked()
{
    player->pause();
}

void MainWindow::on_pushButton_6_clicked()
{
    player->stop();
}

void MainWindow::on_btn_silent_clicked()
{
    bool mute=player->isMuted();
    player->setMuted(!mute);
    if(mute)
        ui->btn_silent->setIcon(QIcon(":/images/images/volumn.bmp"));
    else {
        ui->btn_silent->setIcon(QIcon(":/images/images/mute.bmp"));
    }
}

void MainWindow::on_slider_volume_valueChanged(int value)
{
    player->setVolume(value);
}

void MainWindow::on_slider_time_valueChanged(int value)
{
    player->setPosition(value);
}


void MainWindow::on_cmb_rate_currentIndexChanged(const QString &arg1)
{
    double rate=arg1.toDouble();
    qDebug()<<rate;
    player->setPlaybackRate(rate);
}
