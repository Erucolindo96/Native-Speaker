#ifndef FILEMODELDAO_HPP
#define FILEMODELDAO_HPP
#include"dao/ModelDao.hpp"
#include<alize.h>
#include<stdexcept>
#include"exceptions/simple_exceptions.hpp"
#include"models/diagonal_model.hpp"
#include<map>
#include<QtCore/QDir>


/**
 * @brief The FileModelDao Klasa zapisująca model do pliku w formacie .xml
 * Pobiera typ modelu, który ma utworzyć przy odczycie z pliku. Na razie działa tylko dla DiagonalModel.
 * Docelowo powinno odczytywać typ modelu na podstawie rozszerzenia pliku. Na razie tego nie robi.
 * Pobiera również długość wektora(potrzebna przy inicjalizacji modelu)
 */

class FileModelDao : public ModelDao
{
protected:
  std::string models_dir_;
  uint32_t vect_size_;
//  alize::DistribType t_;

  alize::Config createConfig(const std::string &file_name)const;
  std::unique_ptr<GmmModel> createModel(const alize::MixtureServer &s)const;
  const char* ext()const;


public:

  explicit FileModelDao() = default;
  FileModelDao(const FileModelDao &other) = default;
  FileModelDao& operator =(const FileModelDao &other) = default;
  FileModelDao(FileModelDao &&other) = default;
  FileModelDao& operator =(FileModelDao &&other) = default;
/*
  alize::DistribType getDistribType()const;
  void setDistribType(alize::DistribType t);
*/
  uint32_t getVectSize()const;
  void setVectSize(uint32_t v_size);

  std::string getModelsDir()const;
  void setModelsDir(const std::string new_dir);

  void writeModel(const GmmModel &m)const override;
  std::unique_ptr<GmmModel> readModel(const std::string &model_name)override;

  std::vector<std::unique_ptr<GmmModel> > readAllModels()override;


};

#endif // FILEMODELDAO_HPP
