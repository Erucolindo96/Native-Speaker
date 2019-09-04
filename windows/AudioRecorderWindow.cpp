#include "AudioRecorderWindow.hpp"

AudioRecorderWindow::AudioRecorderWindow(QWidget *parent) :
  QDialog(parent), recorder_(std::make_unique<QAudioRecorder>()),
  player_(std::make_unique<QMediaPlayer>()),
  rec_timer_(std::make_shared<QTimer>())
{
  ui_.setupUi(this);
  initalizeUi();

  rec_timer_->setInterval(1000);//aby odliczał sekundy nagrania
  connect(recorder_.get(), SIGNAL(stateChanged(QMediaRecorder::State)),
          this, SLOT(onStateChange(QMediaRecorder::State)));
  connect(player_.get(), SIGNAL(stateChanged(QMediaPlayer::State)),
          this, SLOT(onStateChange(QMediaPlayer::State)) );

  connect(rec_timer_.get(), SIGNAL(timeout()),
          this, SLOT(incrementRecordTime()));

  connect(recorder_.get(), SIGNAL(error(QMediaRecorder::Error)),
          this, SLOT(recordErrorHandler(QMediaRecorder::Error)) );
  connect(player_.get(), SIGNAL(error(QMediaPlayer::Error)),
          this, SLOT(playingErrorHandler(QMediaPlayer::Error))  );

//  QMediaPlayer p;
//  QMediaPlaylist *list = new QMediaPlaylist;
//  list->addMedia(QUrl::fromLocalFile("home/erucolindo/clip_0013.wav"));
//  p.setPlaylist(list);
//  p.play();
//  qDebug()<<p.state();
//  qDebug()<<p.error();

}

std::vector<Record> AudioRecorderWindow::getRegisteredRecords()const
{
  const uint32_t REC_CNT = ui_.listWidget_rec_list->count();
  std::vector<Record> ret(REC_CNT);
  Record r;
  for(uint32_t i = 0; i<REC_CNT; ++i)
  {
    r.setPath(ui_.listWidget_rec_list->item(i)->text());
    ret[i] = r;
  }
  return ret;
}

void AudioRecorderWindow::on_pushButton_record_released()
{
  if(recorder_->state() == QMediaRecorder::StoppedState)
  {
    setSettingToRecorder();
    recorder_->record();
  }
  else
  {
    recorder_->stop();
    addRecordToRegistered();
  }

}

void AudioRecorderWindow::on_pushButton_pause_released()
{
  if(recorder_->state() == QAudioRecorder::RecordingState)
  {
    recorder_->pause();
  }
  else if(recorder_->state() == QAudioRecorder::PausedState)
  {
    recorder_->record();
  }
}

void AudioRecorderWindow::on_toolButton_released()
{
  auto out_path = QFileDialog::getSaveFileName(this, QString(), QString(), "Wav (*.wav)");
  ui_.lineEdit_rec_path->setText(out_path);
}



void AudioRecorderWindow::on_pushButton_play_released()
{
  if(player_->state() == QMediaPlayer::StoppedState)
  {
    setSettingToPlayer();
    player_->play();
  }
  else
  {
    player_->stop();
  }
}
void AudioRecorderWindow::on_pushButton_pause_play_released()
{
  if(player_->state() == QMediaPlayer::PlayingState)
  {
    player_->pause();
  }
  else if(player_->state() == QMediaPlayer::PausedState)
  {
    player_->play();
  }
}




void AudioRecorderWindow::onStateChange(const QMediaRecorder::State s)
{
  //3 stany - brak nagrywania, nagrywanie, pauza
  switch(s)
  {
    case QAudioRecorder::StoppedState:
      ui_.pushButton_record->setText(REC_TEXT_BUTTON);
      ui_.pushButton_pause->setDisabled(true);
      ui_.lineEdit_rec_path->clear();
      rec_timer_->stop();
      ui_.lcdNumber_rec_time->display(0);
      break;
    case QAudioRecorder::RecordingState:
      ui_.pushButton_record->setText(STOP_TEXT_BUTTON);
      ui_.pushButton_pause->setEnabled(true);
      ui_.pushButton_pause->setText(PAUSE_TEXT_BUTTON);
      rec_timer_->start();
      break;
    case QAudioRecorder::PausedState:
      ui_.pushButton_record->setText(STOP_TEXT_BUTTON);
      ui_.pushButton_pause->setEnabled(true);
      ui_.pushButton_pause->setText(CONTINUE_TEXT_BUTTON);
      rec_timer_->stop();
      break;
    default:
      break;
  }
}

void AudioRecorderWindow::onStateChange(const QMediaPlayer::State s)
{
  //3 stany - brak odtwarzania, odtwarzanie, pauza
  switch(s)
  {
    case QMediaPlayer::StoppedState:
      ui_.pushButton_play->setText(PLAY_TEXT_BUTTON);
      ui_.pushButton_pause_play->setDisabled(true);
      break;
    case QMediaPlayer::PlayingState:
      ui_.pushButton_play->setText(STOP_TEXT_BUTTON);
      ui_.pushButton_pause_play->setEnabled(true);
      ui_.pushButton_pause_play->setText(PAUSE_TEXT_BUTTON);
      break;
    case QMediaPlayer::PausedState:
      ui_.pushButton_play->setText(STOP_TEXT_BUTTON);
      ui_.pushButton_pause_play->setEnabled(true);
      ui_.pushButton_pause_play->setText(CONTINUE_TEXT_BUTTON);
      break;
    default:
      break;
  }
}


void AudioRecorderWindow::incrementRecordTime()
{
  int32_t act_time = ui_.lcdNumber_rec_time->intValue();
  ui_.lcdNumber_rec_time->display(act_time + 1);
}

void AudioRecorderWindow::recordErrorHandler(QMediaRecorder::Error error)
{
  rec_timer_->stop();
  QMessageBox::warning(this, "Error",
                       "Error occur while recording. Recording abort.",
                       QMessageBox::Ok);

}


void AudioRecorderWindow::playingErrorHandler(QMediaPlayer::Error error)
{
  QMessageBox::warning(this, "Error",
                       "Error occur while playing. Playing abort.",
                       QMessageBox::Ok);
}


void AudioRecorderWindow::initalizeUi()
{
  //devices
  const QStringList DEVICES = recorder_->audioInputs();
  ui_.comboBox_device->insertItems(0, DEVICES);
  //formats
  ui_.comboBox_out_codec->insertItems(0,
                                      recorder_->supportedAudioCodecs()
                                      );
  ui_.comboBox_out_container->insertItems(0,
                                          recorder_->supportedContainers());
  //sample rates
  const QStringList S_RATES = {"8000", "11025", "22050", "44100", "48000"};
  ui_.comboBox_s_rate->insertItems(0, S_RATES);

  //bitrates
  const QStringList BITRATES = {"32000"};
  ui_.comboBox_bitrate->insertItems(0,BITRATES );

}


void AudioRecorderWindow::setSettingToRecorder()
{
  recorder_->setAudioInput(ui_.comboBox_device->currentText());

  QAudioEncoderSettings s;
  s.setCodec(ui_.comboBox_out_codec->currentText());
  s.setSampleRate(ui_.comboBox_s_rate->currentText().toInt());
  s.setBitRate(ui_.comboBox_bitrate->currentText().toInt());
  s.setEncodingMode(QMultimedia::ConstantBitRateEncoding);
  auto container = ui_.comboBox_out_container->currentText();

  s.setChannelCount(1);
  recorder_->setEncodingSettings(s, QVideoEncoderSettings(), container);

  recorder_->setOutputLocation(QUrl(ui_.lineEdit_rec_path->text()));

}

void AudioRecorderWindow::setSettingToPlayer()
{
  QMediaPlaylist *playlist = new QMediaPlaylist;
  auto selected_recs = ui_.listWidget_rec_list->selectedItems();
  if(!selected_recs.empty())
  {
    for(auto w_item: selected_recs)
    {
      cout<<w_item->text().toStdString()<<endl;
      cout<<QUrl::fromLocalFile(w_item->text()).toString().toStdString()<<endl;
      cout<<QUrl::fromLocalFile(w_item->text()).isValid()<<endl;
      playlist->addMedia(QUrl::fromLocalFile(w_item->text()));
    }
  }
  player_->setPlaylist(playlist);
}

void AudioRecorderWindow::addRecordToRegistered()
{
  Record r;
  try{
    r.setPath(recorder_->outputLocation().toLocalFile());
  }catch(FileNotFound &e)
  {
    QMessageBox::warning(this, "Record was not correctly save",
                         "Record was not correctly save. Maybe yow have no rights to save record at that path?",
                         QMessageBox::Ok);
    return;
  }
  ui_.listWidget_rec_list->addItem(r.getRecordInfo().absoluteFilePath());

}





