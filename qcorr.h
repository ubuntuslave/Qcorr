#ifndef QCORR_H
#define QCORR_H

#include <QtGui/QMainWindow>

#include "ui_qcorr.h"

class QImage;
class QPainter;

class Qcorr : public QMainWindow, private Ui::QcorrClass
{
    Q_OBJECT

public:
    Qcorr(QWidget *parent = 0);
    ~Qcorr();

private Q_SLOTS:
    void browseLeftImage();
    void browseRightImage();
//    void convertImage();
//    void updateOutputTextEdit();
//    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
//    void processError(QProcess::ProcessError error);
    void displayImage(QImage *image, QLabel *label);
private:
    QImage *m_leftImage;
    QImage *m_rightImage;
};

#endif // QCORR_H
