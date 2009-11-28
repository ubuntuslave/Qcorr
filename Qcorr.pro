TEMPLATE = app
TARGET = Qcorr
QT += core \
    gui
HEADERS += src/corrmethod.h \
    src/globals.h \
    src/imgLabel.h \
    src/qcorr.h \
    src/targetImgLabel.h
SOURCES += src/corrmethod.cpp \
    src/imgLabel.cpp \
    src/main.cpp \
    src/qcorr.cpp \
    src/targetImgLabel.cpp
FORMS += src/corrmethod.ui \
    src/qcorr.ui
RESOURCES += 
