#ifndef AUDIORECORDERWINDOW_HPP
#define AUDIORECORDERWINDOW_HPP

#include "ui_AudioRecorderWindow.h"
#include"record-base/Record.hpp"
#include<QAudioRecorder>
#include<vector>
#include"record-base/RecordFormatFactory.hpp"
#include<QMessageBox>
#include<QUrl>
#include<QTimer>
#include<QFileDialog>
#include<QMediaPlayer>
#include<QMediaPlaylist>
class AudioRecorderWindow : public QDialog
{
  Q_OBJECT

public:
  explicit AudioRecorderWindow(QWidget *parent = 0);

  std::vector<Record> getRegisteredRecords()const;

private slots:
  void on_pushButton_pause_released();
  void on_pushButton_record_released();

  void on_toolButton_released();

  void on_pushButton_play_released();
  void on_pushButton_pause_play_released();

  void onStateChange(const QMediaRecorder::State s);
  void onStateChange(const QMediaPlayer::State s);

  void incrementRecordTime();

  void recordErrorHandler(QMediaRecorder::Error error);
  void playingErrorHandler(QMediaPlayer::Error error);



private:
  Ui::AudioRecorderWindow ui_;
  //std::vector<Record> registered_records_;
  std::unique_ptr<QAudioRecorder> recorder_;
  std::unique_ptr<QMediaPlayer> player_;
  std::shared_ptr<QTimer> rec_timer_;
  const QString STOP_TEXT_BUTTON = "Stop", REC_TEXT_BUTTON = "Record",
  PAUSE_TEXT_BUTTON = "Pause", CONTINUE_TEXT_BUTTON = "Continue",
  PLAY_TEXT_BUTTON = "Play";

  void initalizeUi();
  void setSettingToRecorder();
  void setSettingToPlayer();
  void addRecordToRegistered();
  bool checkOutputPath(const QString validating_path);


};

#endif // AUDIORECORDERWINDOW_HPP
