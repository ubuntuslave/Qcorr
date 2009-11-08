#ifndef QCORR_H
#define QCORR_H

#include <QtGui/QMainWindow>

#include "ui_qcorr.h"

class QImage;
class QPainter;
class QScrollBar;

class Qcorr : public QMainWindow, private Ui::QcorrClass
{
    Q_OBJECT

public:
    Qcorr(QWidget *parent = 0);
    ~Qcorr();

private Q_SLOTS:
    void browseLeftImage();
    void browseRightImage();
    void displayImage(QImage *image, QLabel *label);
private:
    void createActions();
    void setImageLabels();
//    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage *m_leftImage;
    QImage *m_rightImage;
    QLabel *leftImage_label;
    QLabel *rightImage_label;
};

#endif // QCORR_H
