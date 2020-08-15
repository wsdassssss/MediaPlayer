#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QString durationtime;
    QString postiontime;
    void system_init();
private slots:
    void onStateChanged(QMediaPlayer::State state);
    void onPlaylistChanged(int position);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_btn_silent_clicked();

    void on_slider_volume_valueChanged(int value);

    void on_slider_time_valueChanged(int value);


    void on_cmb_rate_currentIndexChanged(const QString &arg1);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void test();
private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
