#include "FileModelDao.hpp"



alize::Config FileModelDao::createConfig(const std::string &file_name)const
{
  alize::Config conf;
  conf.setParam("saveMixtureFileFormat", "XML");
  conf.setParam("saveMixtureFileExtension", ext());
  conf.setParam("saveMixtureServerFileFormat", "XML");
  conf.setParam("saveMixtureServerFileExtension", ext());
  conf.setParam("loadMixtureFileFormat", "XML");
  conf.setParam("loadMixtureFileExtension", ext());
  conf.setParam("mixtureFilesPath", models_dir_.c_str());
  conf.setParam("vectSize", std::to_string(vect_size_).c_str());
  return conf;
}

std::unique_ptr<GmmModel> FileModelDao::createModel(const alize::MixtureServer &s)const
{
  alize::DistribType type = GmmModel::getDistribTypeOfServer(s);
  uint32_t distrib_cnt = GmmModel::getDistribCountOfServer(s);
  std::unique_ptr<GmmModel>  ptr;
  if(type == alize::DistribType_GD)
  {
    ptr = std::make_unique<DiagonalModel>(distrib_cnt, vect_size_);
  }
  else if(type == alize::DistribType_GF)
  {
    throw std::runtime_error("TODO");
  }
  GmmModel::copyDataFromMixtureServer(s, *ptr);
  ptr->setName(s.getServerName().c_str());
  return ptr;
}

const char* FileModelDao::ext()const
{
  return ".xml";
}



uint32_t FileModelDao::getVectSize()const
{
  return vect_size_;
}

void FileModelDao::setVectSize(uint32_t v_size)
{
  vect_size_ = v_size;
}


std::string FileModelDao::getModelsDir()const
{
  return models_dir_;
}
void FileModelDao::setModelsDir(const std::string new_dir)
{
  models_dir_ = new_dir;
}

void FileModelDao::writeModel(const GmmModel &m)const
{
  if(m.getName().empty())
  {
    throw ModelNameNotDefined(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                              + std::string(" - model name not defined while writing model to file"));
  }
  if(m.getFeatureVectorSize() != vect_size_)
  {
    throw InvalidFeatureSize(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                             + std::string(" - model have another vect size than dao"));
  }
  alize::Config conf = createConfig(m.getName());
  alize::MixtureServerFileWriter writer(m.getName().c_str(),conf);
  writer.writeMixtureServer(*(m.getMixtureServerRef()));
  writer.close();
}
std::unique_ptr<GmmModel> FileModelDao::readModel(const std::string &model_name)

{
  if(model_name.empty())
  {
    throw ModelNameNotDefined(__FILE__ + std::string(", line: ") + std::to_string(__LINE__)
                              + std::string(" - try to read model with empty name"));
  }
  try
  {
    alize::Config conf = createConfig(model_name);
    alize::MixtureServerFileReaderXml reader(model_name.c_str(), conf);
    alize::MixtureServer s(conf);
    reader.readMixtureServer(s);
    return createModel(s);
  }
  catch(alize::FileNotFoundException &e)
  {
    throw FileNotFound(e.toString().c_str());
  }
}
