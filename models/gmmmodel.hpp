#ifndef GMMMODEL_HPP
#define GMMMODEL_HPP

#include <alize/alize.h>
#include<memory>
#include <stdexcept>
#include <vector>
#include "models/learning_algo.hpp"
#include"exceptions/simple_exceptions.hpp"

class GmmModel
{
protected:


  const uint32_t DISTRIB_CNT, FEATURE_SIZE;
  const double MAX_LLK = 100.0, MIN_LLK = -100.0;
  std::unique_ptr<alize::MixtureServer> s_;
  alize::DistribType type_;
  std::vector<alize::Feature> features_;

  virtual void initDefaultMixture(uint32_t distrib_cnt);

  alize::Mixture& getMixtureRef()const;
public:
  GmmModel() = delete;
  explicit GmmModel(uint32_t distrib_cnt, uint32_t feature_size);
  explicit GmmModel(uint32_t distrib_cnt, uint32_t feature_size, const std::string &name);
  GmmModel(const GmmModel &other) = delete;
  GmmModel& operator=(const GmmModel &other) = delete;

  GmmModel(GmmModel &&other);
  GmmModel& operator =(GmmModel &&other) = delete;

  void addTrainingFeature(const alize::Feature &feature);
  void addTrainingFeature(const std::vector<alize::Feature> &vec);
  std::vector<alize::Feature> getTrainingFeatures()const;

  void setName(const std::string &name);
  std::string getName()const;

  alize::DistribType getType()const;

  const std::unique_ptr<alize::MixtureServer>& getMixtureServerRef()const;

  virtual double countLikehoodWithWeight(const alize::Feature &arg)const;
  virtual double countLikehoodWithWeight(const alize::Feature &arg, uint32_t distrib_idx)const;
  virtual double countLikehoodWithWeight(const std::vector<alize::Feature> &arg)const;

  uint32_t getDistribCount()const;
  double getDistribWeight(uint32_t distrib_idx)const;
  void setDistribWeight(uint32_t distrib, double new_weight);

  alize::RealVector<double> getDistribMean(uint32_t distrib)const;
  void setDistribMean(uint32_t distrib, const alize::RealVector<double> &new_mean);

  virtual void setDistribCovariance(uint32_t distrib, const alize::RealVector<double> &diagonal_covariance) = 0;
  virtual void setDistribCovariance(uint32_t distrib, const alize::DoubleMatrix &covariance) = 0;

  virtual alize::RealVector<double> getDistribCovariance(uint32_t distrib)const = 0;


  uint32_t getFeatureVectorSize()const;

  virtual ~GmmModel() = default;
  static std::vector<alize::Feature> extractAllFeatures(alize::FeatureServer &s);
  /**
   * @brief getDistribTypeOfServer Interpretuje wskazany jako parametr MixtureServer jako serwer wchodzący w skład klasy
   * i odczytuje, jakiego typu jest utworzona w nim mieszanina - czy GD, czy GF.
   * @param s Badany MIxtureServer
   * @return Typ utworzonej w MixtureServerze mieszaniny Gaussowskiej
   */
  static alize::DistribType getDistribTypeOfServer(const alize::MixtureServer &s);
  /**
   * @brief getDistribCountOfServer Interpretuje wskazany jako parametr MixtureServer jako serwer wchodzący w skład klasy
   * i odczytuje, jak wiele dystrybucji zawiera mieszanina znajdująca sie w serwerze.
   * @param s Badany MixtureServer
   * @return Ilośc dystrybucji utworzonej w MixtureServerze mieszaniny Gaussowskiej
   */
  static uint32_t getDistribCountOfServer(const alize::MixtureServer &s);

  /**
   * @brief copyDataFromMixtureServer Interpretuje wskazany jako parametr MixtureServer jako serwer wchodzący w skład klasy
   * i kopiuje znajdującą się w nim mieszaninę gaussowską.
   * @param s MixtureServer z którego pobieramy miksturę
   * @param model Model, do którego zapisujemy miksturę
   * @throw InvalidModelType Jesli typ misktury w serwerze nie zgadza się z typem modelu
   */
  static void copyDataFromMixtureServer(const alize::MixtureServer &s, GmmModel &model);
};

#endif // GMMMODEL_HPP
