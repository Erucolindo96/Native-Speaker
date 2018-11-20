#-------------------------------------------------
#
# Project created by QtCreator 2018-07-07T23:13:06
#
#-------------------------------------------------


TEMPLATE = subdirs
SUBDIRS = common main \
      models/tests/diagonal-model-test \
      models/tests/em-algo-test \
      utils/tests/utils-test \
      dao/tests/dao-test \
      features/tests/feature-readers-tests \



models/tests/em-algo-test.depends = common
utils/tests/utils-test.depends = common
models/tests/diagonal-model-test.depends = common
main.depends = common
dao/tests/dao-test.depends = common
