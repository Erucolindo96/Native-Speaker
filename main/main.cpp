#include<alize/alize.h>

#include"models/diagonal_model.hpp"
#include"models/verificator.hpp"
#include"features/FeatureReaderSilenceCutter.hpp"
#include"models/learning_algo.hpp"
#include"utils/utils.hpp"
#include"dao/FileModelDao.hpp"
#include"windows/MainWindow.hpp"
#include<QtCore/QDir>
#include<QAudioRecorder>
#include"features/FeatureManager.hpp"
#include"record-base/RecBaseManager.hpp"
#include"models/ModelManager.hpp"
#include<QMetaType>
#include"cmd-main/CliMain.hpp"

using namespace std;
using namespace alize;
using namespace utils;


/**
 *
 * Mozliwe formaty komend:
 *
 * w każdej komendzie, poza wyświetleniem pomocy, nalezy podać ścieżke konfiguracji
 *
 * -c <config_path>
 *
 * 1. -C -m <model_name> -d <d_cnt> - tworzenie nowego modelu
 * 2. -L -m <model_name> -s <training_recs_dir> -i <iter_cnt> -a <algo_name> - uczenie wskazanego modelu
 * 3. -V -m <model_name> -u <ubm_name> -r <record_path> -t <threshold> - weryfikacja
 * 4. -D -m <model_name> -u <ubm_name> -r <record_path> - roznica LLK modelu i UBM
 * 5. -h,--help - wyświetlenie pomocy
 *
 * Konfiguracje nalezy utworzyć ręcznie, albo za pomocą gui
 *
 *
*/
int main(int argc, char *argv[])
{
  try
  {
    if(argc > 1)//uruchamiamy komende konsolową, nie gui
    {
      CliMain app(argc, argv);
      app.execute();
      return 0;
    }
    QApplication app(argc, argv);
    std::unique_ptr<MainWindow> window = make_unique<MainWindow>();
    window->show();
    return app.exec();
  }
  catch(alize::Exception &e)
  {
    cout<<e.toString().c_str()<<endl;
  }
  catch(std::exception &e)
  {
    cout<<e.what()<<endl;
  }
  return 0;

}
