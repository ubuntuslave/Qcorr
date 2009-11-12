#ifndef QCORR_H
#define QCORR_H

#include <QtGui/QMainWindow>

#include "ui_qcorr.h"
#include "imgLabel.h"

class QImage;
class QPainter;
class QScrollBar;

class Qcorr : public QMainWindow, private Ui::QcorrClass
{
    Q_OBJECT

public:
    Qcorr(QWidget *parent = 0);
    ~Qcorr();

    friend class ImgLabel; // Make the ImgLabel class a friend of Qcorr
                            // Thus, so members from Qcorr are accessible by an ImgLabel object

private Q_SLOTS:
    void browseLeftImage();
    void browseRightImage();
    void displayImage(QImage *image, QLabel *label);
    void displayImageLabel(QImage *image, ImgLabel *label);
//    void displayCoordinates(QLabel *label, QPointF *point);
private:
    void createActions();
    void setImageLabels();
//    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage *m_leftImage;
    QImage *m_rightImage;
//    QLabel *leftImage_label;
    ImgLabel *leftImage_label;
    QLabel *rightImage_label;
    QLabel *m_status_label;
    QLabel *m_location_label;



//protected:
//    void paintEvent(QPaintEvent *event);
//    void mousePressEvent(QMouseEvent *event);
};


// TO DO:
// Spacebar opens full screen mode on image.

#endif // QCORR_H
