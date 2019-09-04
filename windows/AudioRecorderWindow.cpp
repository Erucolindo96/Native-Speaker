#include "AudioRecorderWindow.hpp"

AudioRecorderWindow::AudioRecorderWindow(QWidget *parent) :
  QDialog(parent), recorder_(nullptr),
  player_(std::make_unique<QMediaPlayer>()),
  rec_timer_(std::make_shared<QTimer>())
{
  cout<<"przed ui"<<endl;
  ui_.setupUi(this);
  initalizeUi();
  cout<<"initialize ui"<<endl;

  rec_timer_->setInterval(1000);//aby odliczał sekundy nagrania

  connect(player_.get(), SIGNAL(stateChanged(QMediaPlayer::State)),
          this, SLOT(onStateChange(QMediaPlayer::State)) );

  connect(rec_timer_.get(), SIGNAL(timeout()),
          this, SLOT(incrementRecordTime()));


  connect(player_.get(), SIGNAL(error(QMediaPlayer::Error)),
          this, SLOT(playingErrorHandler(QMediaPlayer::Error))  );
  cout<<"po connectach"<<endl;

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
    if(recorder_ != nullptr && recorder_->state() == QAudio::ActiveState)//nagrywa
    {//trzeba zatrzymac
        recorder_->stop();
        addRecordToRegistered();
        rec_file_.close();
        convertRecordToContainer();
    }
    else if(recorder_ == nullptr || recorder_->state() == QAudio::StoppedState)
    {//albo nie byl uruchamiany, albo byl ale zostal zatrzymany
        //wiec trzeba ruszyc nagrywanie
        prepareFileToRecord();
        createRecorder();
        recorder_->start(&rec_file_);
    }
    else
    {
        QMessageBox::warning(this, "Error", "State not defined while clicking on record/stop button. Rec abort.", QMessageBox::Ok);
        if(recorder_ != nullptr)
        {
            qWarning()<<"State number: "<<recorder_->state();
            recorder_->stop();
            rec_file_.close();
            delete recorder_;
        }
    }

}

void AudioRecorderWindow::on_pushButton_pause_released()
{
    if(recorder_ != nullptr)
    {
        if(recorder_->state() == QAudio::ActiveState)
        {
            recorder_->suspend();
        }
        else if(recorder_->state() == QAudio::SuspendedState)
        {
            recorder_->resume();
        }
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




void AudioRecorderWindow::onStateChange(const QAudio::State s)
{
  //3 stany - brak nagrywania, nagrywanie, pauza
  switch(s)
  {
    case QAudio::StoppedState:
      ui_.pushButton_record->setText(REC_TEXT_BUTTON);
      ui_.pushButton_pause->setDisabled(true);
      ui_.lineEdit_rec_path->clear();
      rec_timer_->stop();
      ui_.lcdNumber_rec_time->display(0);
      break;
    case QAudio::ActiveState:
      ui_.pushButton_record->setText(STOP_TEXT_BUTTON);
      ui_.pushButton_pause->setEnabled(true);
      ui_.pushButton_pause->setText(PAUSE_TEXT_BUTTON);
      rec_timer_->start();
      break;
    case QAudio::SuspendedState:
      ui_.pushButton_record->setText(STOP_TEXT_BUTTON);
      ui_.pushButton_pause->setEnabled(true);
      ui_.pushButton_pause->setText(CONTINUE_TEXT_BUTTON);
      rec_timer_->stop();
      break;
    default:
      qWarning()<<"unexpected state: "<<s;
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

void AudioRecorderWindow::recordErrorHandler(QAudio::Error error)
{
  rec_timer_->stop();
  QMessageBox::warning(this, "Error",
                       "Error occur while recording. Recording abort.",
                       QMessageBox::Ok);
  qWarning()<<"Error while recording: "<<error;

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
  const auto DEVICES = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
  QStringList DEVICES_STR;
  for(auto dev: DEVICES)
  {
      DEVICES_STR.append(dev.deviceName());
  }
  ui_.comboBox_device->insertItems(0, DEVICES_STR);
  //formats
  ui_.comboBox_out_codec->insertItem(0, "audio/pcm");

  ui_.comboBox_out_container->insertItem(0,"wav");

  //sample rates
  const QStringList S_RATES = {"8000", "11025","16000", "22050", "44100"};
  ui_.comboBox_s_rate->insertItems(0, S_RATES);
  //sample_size
  const QStringList S_SIZES = {"16"};
  ui_.comboBox_sample_size->insertItems(0, S_SIZES);


//  //bitrates
//  const QStringList BITRATES = {"32000"};
//  ui_.comboBox_bitrate->insertItems(0,BITRATES );

}


void AudioRecorderWindow::createRecorder()
{
    QAudioFormat format;
    format.setCodec(ui_.comboBox_out_codec->currentText());
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleRate(ui_.comboBox_s_rate->currentText().toInt());
    format.setSampleSize(ui_.comboBox_sample_size->currentText().toInt());
    format.setChannelCount(1);
    format.setSampleType(QAudioFormat::SignedInt);
    QString dev_str = ui_.comboBox_device->currentText();
    auto devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    auto dev_iter = std::find_if(devices.begin(), devices.end(),
                                 [dev_str](auto d)->bool
    {
        return dev_str == d.deviceName();
    });

    QAudioDeviceInfo dev_to_record;
    if(dev_iter == devices.end())
    {
        QMessageBox::warning(this, "Device error", "No such device like checked by user. Try to use default.", QMessageBox::Ok);
        qWarning()<<"Dev not found: "<<dev_str;
        dev_to_record = QAudioDeviceInfo::defaultInputDevice();
    }
    else
    {
        dev_to_record = *dev_iter;
    }
    if (!dev_to_record.isFormatSupported(format)) {
        qWarning() << "Default format not supported";
    }

    if(recorder_ != nullptr)
    {
        delete recorder_;
    }
    recorder_ = new QAudioInput(dev_to_record, format);
    connectRecorderSlot();
}

void AudioRecorderWindow::prepareFileToRecord()
{
    rec_file_.setFileName(ui_.lineEdit_rec_path->text() + ".raw");
    rec_file_.open(QFile::WriteOnly | QFile::Truncate);
}


void AudioRecorderWindow::convertRecordToContainer()
{

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
    r.setPath(rec_file_.fileName());
  }catch(FileNotFound &e)
  {
    QMessageBox::warning(this, "Record was not correctly save",
                         "Record was not correctly save. Try to rerun recording.",
                         QMessageBox::Ok);
    return;
  }
  ui_.listWidget_rec_list->addItem(r.getRecordInfo().absoluteFilePath());

}


  void AudioRecorderWindow::connectRecorderSlot()
  {
      connect(recorder_, SIGNAL(stateChanged(QAudio::State)),
              this, SLOT(onStateChange(QAudio::State)));
  }


