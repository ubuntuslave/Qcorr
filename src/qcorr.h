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

/** @ingroup classes */
/** @{ */
/** @defgroup qcorr_mainwindow Qcorr

 @class Qcorr "src/qcorr.h"

 @ingroup qcorr_mainwindow

 @brief A Digital Image Correlation Program (Template Matcher) implemented in QT4

 This class combines all other sub-classed QWidgets implemented throughout the program. The main correlation (template matching) functionality is implemented in this class through the procedure convertToGrayScaleFloat()

 @note

 Correlation is performed on gray-scale (1 channel image) that are computed in this procedure through the convertToGrayScaleFloat() function.

 @par  Compile-time dependencies

 - The QT4 Framework

 @bug
 - Perhaps a few, but not noticed so far.

 @todo
 - Add Stereo functionality to obtain disparity maps

 @author Carlos Jaramillo
 @author Joel Gonzalez

 */
/** @} */

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

    /** @brief  Cross-correlation of target image with template image.
    * @note Correlation is performed on gray-scale (1 channel image) that are computed in this procedure through the convertToGrayScaleFloat() function.
    * @param imgTarget Buffer of unsigned characters containing the target image where correlation match is to be found
    * @param nWI Width of target image
    * @param nHI Height of target image
    * @param nDepthI Pixel depth of target image
    * @param imgTemplate Buffer of unsigned characters containing the template image
    * @param nWT Width of target image
    * @param nHT Height of target image
    * @param nDepthT Pixel depth of target image
    * @param rnDx X position where the highest level of correlation match is found (top-left corner of the match)
    * @param rnDy Y position where the highest level of correlation match is found (top-left corner of the match)
    * @param method Determines the selected method to be used in the correlation process. The method is a globally defined enumeration.
    *       The available methods are:
    *       - CROSS_CORR (cross correlation):
    *        \f[
    *             C(u,v) = \frac
    *                      {\sum{\left\{T(x,y) * I(x-u,y-v)\right\}}}
    *                      {\sqrt{ \sum{I(x-u,y-v)^2}}}
    *
    *        \f]
    *       - SUM_SQ_DIFF (sum of squared differences):
    *        \f[
    *             C(u,v) = \frac
    *                      {\sum{\left\{T(x,y)-I(x-u,y-v)\right\}^2}}
    *                      {\sqrt{\sum{I(x-u,y-v)^2}}}
    *        \f]
    *       - CORR_COEFF (correlation coefficient):
    *        \f[
    *             C(u,v) = \frac
    *                      {\sum{\left\{(T(x,y)-T_{avg}) * (I(x-u,y-v)-I_{avg})\right\}}}
    *                      {\sqrt{\sum{(T(x,y)-T_{avg})^2} * \sum{(I(x-u,y-v)-I_{avg})^2}}}
    *        \f]
    * @param multires Determines if multiresolution correlation should be applied, by making use of image pyramids.
    *                 With multiresoltion, the correlation can be determined faster than direct correlation.
    * @returns a float array resulting from the conversion of the source image into an 8-bit gray-scale image.
    */
    float findCorrelation(const unsigned char * imgTarget, const int nWI, const int nHI, const int nDepthI,
          const unsigned char * imgTemplate, const int nWT, const int nHT, const int nDepthT,
          int &rnDx, int &rnDy, int nMethod, bool bMultires);

    /** @brief  Cast images to an 8-bit gray-scale channel of type float
      * @param pchImgOriginalBits Buffer of unsigned characters as the source image
      * @param nSize Number of pixels in the source image
      * @param nDepth Pixel depth of the source image
      * @returns the correlation number computed by method (directly).
      *           Additionally, the (dx,dy) offset of the template for which there exists a best match.
      */
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


// TODO:
// Spacebar opens full screen mode on image.

#endif // QCORR_H
