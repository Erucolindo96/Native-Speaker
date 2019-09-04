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
#include<QAudioInput>
#include<QProcess>
#include"utils/utils.hpp"




class AudioRecorderWindow : public QDialog
{
  Q_OBJECT

public:
  explicit AudioRecorderWindow(QWidget *parent = nullptr);

  std::vector<Record> getRegisteredRecords()const;

private slots:
  void on_pushButton_pause_released();
  void on_pushButton_record_released();

  void on_toolButton_released();

  void on_pushButton_play_released();
  void on_pushButton_pause_play_released();

  void onStateChange(const QAudio::State s);
  void onStateChange(const QMediaPlayer::State s);

  void incrementRecordTime();

  void recordErrorHandler(QAudio::Error error);
  void playingErrorHandler(QMediaPlayer::Error error);



private:
  Ui::AudioRecorderWindow ui_;

  QAudioInput *recorder_;
  QProcess *sox_proc_;
  QString rec_path_;
  std::unique_ptr<QMediaPlayer> player_;
  std::shared_ptr<QTimer> rec_timer_;
  const QString STOP_TEXT_BUTTON = "Stop", REC_TEXT_BUTTON = "Record",
  PAUSE_TEXT_BUTTON = "Pause", CONTINUE_TEXT_BUTTON = "Continue",
  PLAY_TEXT_BUTTON = "Play";

  void initalizeUi();
  void setSettingToPlayer();
  void createRecorder();
  void createSoxProc();
  void createFileInfo();
  void addRecordToRegistered();

  void connectRecorderSlot();

};

#endif // AUDIORECORDERWINDOW_HPP
