include(../include.pri)

TEMPLATE = lib
CONFIG = staticlib

SOURCES += ../feature_generator.cpp \
    ../utils/utils.cpp \
    ../models/diagonal_model.cpp \
    ../models/gmmmodel.cpp \
    ../models/learning_algo.cpp \
#    ../mainwindow.cpp

HEADERS  += ../feature_generator.hpp \
    ../models/diagonal_model.hpp \
    ../models/gmmmodel.hpp \
    ../models/learning_algo.hpp \
    ../utils/utils.hpp \
#    ../mainwindow.hpp

INCLUDEPATH += ..

#FORMS    += ../mainwindow.ui \
#    ../wybormodelu.ui


