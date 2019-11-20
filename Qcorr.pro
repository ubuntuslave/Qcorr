TEMPLATE = app
TARGET = Qcorr
QT += core gui widgets
HEADERS += src/controlswindow.h \
    src/corrmethod.h \
    src/globals.h \
    src/imgLabel.h \
    src/qcorr.h \
    src/targetImgLabel.h
SOURCES += src/controlswindow.cpp \
    src/corrmethod.cpp \
    src/imgLabel.cpp \
    src/main.cpp \
    src/qcorr.cpp \
    src/targetImgLabel.cpp
FORMS += src/controlswindow.ui \
    src/corrmethod.ui \
    src/qcorr.ui
RESOURCES += 
