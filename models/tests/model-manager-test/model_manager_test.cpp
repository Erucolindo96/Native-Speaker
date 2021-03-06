﻿
#include"models/tests/model-manager-test/model_manager_test.hpp"


BOOST_AUTO_TEST_SUITE( initialization )


BOOST_AUTO_TEST_CASE(throwOutOfRangeIfModelWithIndexDoesntExist )
{
  ModelManager manager;
  BOOST_CHECK_THROW(manager[20], std::out_of_range);
}


BOOST_AUTO_TEST_CASE(readCorrectlyAllDiagonalModelsFromDirectoryIfModelDirExistWithSavedModelAndVectSizeAndDistribTypeWereSet)
{
  QDir models_dir("models");
  BOOST_REQUIRE(models_dir.exists());
  const uint32_t FEATURE_SIZE = 12, MODELS_CNT = 4;
  ConfigManager config;
  config.setVectSize(FEATURE_SIZE);
  config.setModelFolder(models_dir.dirName().toStdString());

  ModelManager manager;

  BOOST_REQUIRE_NO_THROW(manager.loadModels(config));
  BOOST_REQUIRE_EQUAL(manager.getModelsCnt(), MODELS_CNT);
  BOOST_CHECK_EQUAL(manager[0]->getName(), "ferus");
  BOOST_CHECK_EQUAL(manager[1]->getName(), "janFigat");
  BOOST_CHECK_EQUAL(manager[2]->getName(), "kasprzak");
  BOOST_CHECK_EQUAL(manager[3]->getName(), "maksymFigat");


}


BOOST_AUTO_TEST_CASE( addCorrectlyNewModelToBaseIfModelDirExistInConfig )
{
  QDir models_dir("models");
  BOOST_REQUIRE(models_dir.exists());
  const uint32_t FEATURE_SIZE = 12, DISTRIB_CNT = 100,
      MODELS_CNT = 4;
  ConfigManager config;
  config.setVectSize(FEATURE_SIZE);
  config.setModelFolder(models_dir.dirName().toStdString() + "/");
  std::unique_ptr<GmmModel> new_model_ptr = make_unique<DiagonalModel>
                                            (DISTRIB_CNT, FEATURE_SIZE, "zenon");
  auto files = models_dir.entryInfoList(QStringList("*.xml"), QDir::Files, QDir::Name);
  BOOST_REQUIRE_EQUAL(files.size(), MODELS_CNT);

  ModelManager manager;

  BOOST_REQUIRE_NO_THROW(manager.addModel(config,std::move(new_model_ptr)));
  BOOST_CHECK_EQUAL(manager[0]->getName(), "ferus");
  BOOST_CHECK_EQUAL(manager[1]->getName(), "janFigat");
  BOOST_CHECK_EQUAL(manager[2]->getName(), "kasprzak");
  BOOST_CHECK_EQUAL(manager[3]->getName(), "maksymFigat");
  BOOST_CHECK_EQUAL(manager[4]->getName(), "zenon");

  files = models_dir.entryInfoList(QStringList("*.xml"), QDir::Files, QDir::Name);

  BOOST_CHECK_EQUAL(files.size(), MODELS_CNT + 1);
  BOOST_CHECK_EQUAL(files[(MODELS_CNT+1)-1].baseName().toStdString(), "zenon");
  BOOST_CHECK_EQUAL(system("rm models/zenon.xml"), 0);
}


BOOST_AUTO_TEST_CASE( correctlyGetNamesListOfModelsIfThereAre4ModelsFromDatabase )
{
  QDir models_dir("models");
  BOOST_REQUIRE(models_dir.exists());
  const uint32_t FEATURE_SIZE = 12,
      MODELS_CNT = 4;
  ConfigManager config;
  config.setVectSize(FEATURE_SIZE);
  config.setModelFolder(models_dir.dirName().toStdString() + "/");
  ModelManager manager;

  manager.loadModels(config);
  BOOST_REQUIRE_EQUAL(manager[0]->getName(), "ferus");
  BOOST_REQUIRE_EQUAL(manager[1]->getName(), "janFigat");
  BOOST_REQUIRE_EQUAL(manager[2]->getName(), "kasprzak");
  BOOST_REQUIRE_EQUAL(manager[3]->getName(), "maksymFigat");
  auto models_list = manager.getModelsNames();
  BOOST_CHECK_EQUAL(models_list.size(), MODELS_CNT );
  BOOST_CHECK_EQUAL(models_list[0], "ferus");
  BOOST_CHECK_EQUAL(models_list[1], "janFigat");
  BOOST_CHECK_EQUAL(models_list[2], "kasprzak");
  BOOST_CHECK_EQUAL(models_list[3], "maksymFigat");

}

BOOST_AUTO_TEST_CASE( correctlyGetModelByNameIfModelExists )
{
  QDir models_dir("models");
  BOOST_REQUIRE(models_dir.exists());
  const uint32_t FEATURE_SIZE = 12;
  ConfigManager config;
  config.setVectSize(FEATURE_SIZE);
  config.setModelFolder(models_dir.dirName().toStdString() + "/");
  ModelManager manager;

  manager.loadModels(config);
  BOOST_REQUIRE_EQUAL(manager[0]->getName(), "ferus");
  BOOST_REQUIRE_EQUAL(manager[1]->getName(), "janFigat");
  BOOST_REQUIRE_EQUAL(manager[2]->getName(), "kasprzak");
  BOOST_REQUIRE_EQUAL(manager[3]->getName(), "maksymFigat");

  BOOST_CHECK_NO_THROW(manager["ferus"]);
  BOOST_CHECK_EQUAL(manager["ferus"]->getName(), "ferus");
  BOOST_CHECK_EQUAL(manager["janFigat"]->getName(), "janFigat");
  BOOST_CHECK_EQUAL(manager["kasprzak"]->getName(), "kasprzak");
  BOOST_CHECK_EQUAL(manager["maksymFigat"]->getName(), "maksymFigat");
}

BOOST_AUTO_TEST_CASE( throwOutOfRangeAnGettingModelByNameIfModelDoesNotExists )
{
  QDir models_dir("models");
  BOOST_REQUIRE(models_dir.exists());
  const uint32_t FEATURE_SIZE = 12;
  ConfigManager config;
  config.setVectSize(FEATURE_SIZE);
  config.setModelFolder(models_dir.dirName().toStdString() + "/");
  ModelManager manager;

  manager.loadModels(config);

  BOOST_CHECK_THROW(manager["fake-model"], out_of_range);
  BOOST_CHECK_THROW(manager["fake-model2"], out_of_range);

}

BOOST_AUTO_TEST_SUITE_END()
