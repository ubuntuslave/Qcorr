TEMPLATE = app
TARGET = Qcorr
QT += core \
    gui
HEADERS += targetImgLabel.h \
    corrmethod.h \
    globals.h \
    corrmethod.h \
    imgLabel.h \
    qcorr.h
SOURCES += targetImgLabel.cpp \
    corrmethod.cpp \
    imgLabel.cpp \
    main.cpp \
    qcorr.cpp
FORMS += corrmethod.ui \
    qcorr.ui
RESOURCES += 
