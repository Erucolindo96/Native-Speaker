#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP
#include<alize.h>

class ConfigManager: protected alize::Config
{

public:
  const alize::String PARAM_UBM_DIR = "ubmModelDir", PARAM_MODEL_DIR = "modelDir",
  PARAM_VECT_SIZE = "vectSize", PARAM_FEATURE_FOLDER = "featureFolder";
  ConfigManager()=default;
  ConfigManager(const ConfigManager &other)=default;
  ConfigManager& operator=(const ConfigManager &other);
  ConfigManager(ConfigManager &&other);
  ConfigManager& operator=(ConfigManager &&other);

  uint32_t getVectSize()const;
  void setVectSize(uint32_t vect_size);

  std::string getModelFolder()const;
  void setModelFolder(std::string folder);

  std::string getUbmFolder()const;
  void setUbmFolder(std::string folder);

  std::string getFeatureFolder()const;
  void setFeatureFolder(std::string folder);

  void load(const alize::FileName &f);
  void save(const alize::FileName &f) const;

  bool isEmpty()const;
  bool haveUbmFolder()const;
  bool haveModelFolder()const;
  bool haveFeatureFolder()const;
  bool haveVectSize()const;
  bool haveAllParams()const;



  virtual ~ConfigManager()=default;
};

#endif // CONFIGMANAGER_HPP
