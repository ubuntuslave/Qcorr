#include "qcorr.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qcorr w;
    w.show();
    return a.exec();
}
