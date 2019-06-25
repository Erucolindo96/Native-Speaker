#include "AudioRecorderWindow.hpp"

AudioRecorderWindow::AudioRecorderWindow(QWidget *parent) :
  QDialog(parent), recorder_(std::make_unique<QAudioRecorder>()),
  rec_timer_(std::make_shared<QTimer>())
{
  ui_.setupUi(this);
  initalizeUi();

  rec_timer_->setInterval(1000);//aby odliczał sekundy nagrania
  connect(recorder_.get(), SIGNAL(stateChanged(QMediaRecorder::State)),
          this, SLOT(onStateChange(QMediaRecorder::State)));
  connect(rec_timer_.get(), SIGNAL(timeout()),
          this, SLOT(incrementRecordTime()));
  connect(recorder_.get(), SIGNAL(error(QMediaRecorder::Error)),
          this, SLOT(recordErrorHandler(QMediaRecorder::Error)));
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

void AudioRecorderWindow::on_toolButton_released()
{
  auto out_path = QFileDialog::getSaveFileName(this, QString(), QString(), "Wav (*.wav)");
  ui_.lineEdit_rec_path->setText(out_path);
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
      //ui_.lineEdit_rec_path->setText(recorder_->actualLocation().toLocalFile());
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


void AudioRecorderWindow::initalizeUi()
{
  //devices
  const QStringList DEVICES = recorder_->audioInputs();
  ui_.comboBox_device->insertItems(0, DEVICES);
  //formats
  ui_.comboBox_out_format->insertItems(0,
                                       RecordFormatFactory::
                                       getValidFormats());
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
  s.setCodec(RecordFormatFactory::getCodec(ui_.comboBox_out_format->currentText()));
  s.setSampleRate(ui_.comboBox_s_rate->currentText().toInt());
  s.setBitRate(ui_.comboBox_bitrate->currentText().toInt());
  s.setEncodingMode(QMultimedia::ConstantBitRateEncoding);
  auto container = RecordFormatFactory::getContainer(ui_.comboBox_out_format->currentText());
  s.setChannelCount(1);
  recorder_->setEncodingSettings(s, QVideoEncoderSettings(), container);

  recorder_->setOutputLocation(QUrl(ui_.lineEdit_rec_path->text()));

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
  //registered_records_.push_back(r);
}

