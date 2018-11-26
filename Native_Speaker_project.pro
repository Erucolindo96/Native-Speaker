#-------------------------------------------------
#
# Project created by QtCreator 2018-07-07T23:13:06
#
#-------------------------------------------------


TEMPLATE = subdirs
SUBDIRS = common main/main.pro \
      tests/unit-tests.pro


tests/unit-tests.pro.depends = common
main/main.pro.depends = common
