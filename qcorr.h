#ifndef QCORR_H
#define QCORR_H

#include <QtGui/QMainWindow>

#include "ui_qcorr.h"
#include "imgLabel.h"
#include "targetImgLabel.h"
#include "corrmethod.h"

class QImage;
class QPainter;
class QSize;
class QPoint;
class QString;


class Qcorr : public QMainWindow, private Ui::QcorrClass
{
    Q_OBJECT

public:
    Qcorr(QWidget *parent = 0);
    ~Qcorr();

private Q_SLOTS:
    void browseLeftImage();
    void browseRightImage();
    void viewCorrMap();
    void correlate();

private:
    friend class ImgLabel; // Make the ImgLabel class a friend of Qcorr
                           // Thus, all members from Qcorr are accessible by an ImgLabel object

    void displayImage(QImage *image, QLabel *label);
    void displayImageLabel(QImage *image, ImgLabel *label);
    void createActions();
    void setImageLabels();

    //Experimental:
//    void displayPainter(QPainter *painter, QLabel *label);


    /** @brief  Cross-correlation of target image with template image.
    * @note Correlation is performed on the first channel of the images only.
    * @param imgTarget Array of bytes for the target image
    * @param nWI Width of target image
    * @param nHI Height of target image
    * @param nDepthI Pixel depth of target image
    * @param imgTemplate Array of bytes for the template image
    * @param nWT Width of target image
    * @param nHT Height of target image
    * @param nDepthT Pixel depth of target image
    * @param rnDx X position where the highest level of correlation match is found (top-left corner of the match)
    * @param rnDy Y position where the highest level of correlation match is found (top-left corner of the match)
    * @param method Determines the selected method to be used in the correlation process. The method is a globally defined enumeration.
    *       The available methods are:
    *       CROSS_CORR (cross correlation):
    *             C(u,v) = sum of {T(x,y) * I(x-u,y-v)}
    *                      --------------------------------
    *                      sqrt{ sum of {I(x-u,y-v)^2}}
    *
    *       SUM_SQ_DIFF (sum of squared differences):
    *             C(u,v) = sum of {T(x,y)-I(x-u,y-v)}^2
    *                      ------------------------------
    *                      sqrt{ sum of {I(x-u,y-v)^2}}
    *
    *       CORR_COEFF (correlation coefficient):
    *             C(u,v) = sum of {(T(x,y)-Tavg) * (I(x-u,y-v)-Iavg)}
    *                      -----------------------------------------------------
    *                      sqrt{sum{(T(x,y)-Tavg)^2} * sum{(I(x-u,y-v)-Iavg)^2}}
    *
    * @param multires Determines if multiresolution correlation should be applied, by making use of image pyramids.
    *                 With multiresoltion, the correlation can be determined faster than direct correlation.
    *  @returns the correlation number computed by method (directly).
    *           Additionally, the (dx,dy) offset of the template for which there exists a best match.
    */

    // images are passed with 1 channel already
    float findCorrelation(const unsigned char * imgTarget, const int nWI, const int nHI, const int nDepthI,
          const unsigned char * imgTemplate, const int nWT, const int nHT, const int nDepthT,
          int &rnDx, int &rnDy, int nMethod, bool bMultires);
    // casting float happens inside

    float * convertToGrayScaleFloat(const unsigned char * pchImgOriginalBits, int nSize, int nDepth);
    bool fileDumpQImage(const QString &fileName);

    int m_nXoffset, m_nYoffset;

    CorrMethod *m_corrMethodDialog;
    QString initialName;
    QImage *m_leftImage;
    QImage *m_rightImage;
    QImage *m_templateImage;
    QImage *m_corrMapImage;
    ImgLabel *m_leftImage_label;
    TargetImgLabel *m_targetImage_label;
    QLabel *m_status_label;

    QPoint m_matchingPoint;   ///< upper-left corner point where the correlation match was found
    QSize m_templateSize;


protected:
//    void paintEvent(QPaintEvent *);
//    void mousePressEvent(QMouseEvent *event);
};


// TO DO:
// Spacebar opens full screen mode on image.

#endif // QCORR_H
