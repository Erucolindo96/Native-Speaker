#-------------------------------------------------
#
# Project created by QtCreator 2018-07-07T23:13:06
#
#-------------------------------------------------

include(include.pri)

TEMPLATE = subdirs
SUBDIRS = common main \
      models/tests/diagonal-model-test \
      models/tests/em-algo-test \
      utils/tests/utils-test \


models/tests/em-algo-test.depends = common
utils/tests/utils-test.depends = common
models/tests/diagonal-model-test.depends = common
main.depends = common
