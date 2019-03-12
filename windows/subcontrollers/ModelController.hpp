#ifndef MODELCONTROLLER_HPP
#define MODELCONTROLLER_HPP
#include<QToolBox>
#include"models/ModelManager.hpp"
#include<tuple>
#include"models/GmmModelWidget.hpp"

//class QToolBox;

/**
 * @brief The ModelController class Klasa wyświetlająca dostępne modele w menu głównym.
 * Odpowiada za wyświetlanie modeli i ich odświerzanie.
 * Dzięki temu, że dziedziczy z ModelManager zawiera również metody odpowiadające za pobieranie modeli
 * i ich zapis, oraz posiada dostęp do modeli
 */
class ModelController : public ModelManager
{
  Q_OBJECT

public:
  ModelController(QToolBox *ptr = nullptr, const uint32_t models_on_page = 10);
  ModelController(const ModelController &other) = default;
  ModelController& operator=(const ModelController &other) = default;
  ModelController(ModelController &&other) = default;
  ModelController& operator=(ModelController &&other) = default;

  void setToolBoxPtr(QToolBox *ptr);

  uint32_t getActPage()const;

public slots:
  void refreshDisplayedModels();
  void nextPage();
  void prevPage();

protected:
  const int32_t MODELS_ON_PAGE, MIN_PAGE = 0;
  int32_t act_page_;
  QToolBox *toolbox_ptr_;

  void normalizeActPage();
  void removeToolBoxItems();
/*
  std::pair<uint32_t, uint32_t> getIndexFirstAndLastModelAtPage(uint32_t act_page)const;
*/
  int32_t MAX_PAGE()const;


};

#endif // MODELCONTROLLER_HPP
