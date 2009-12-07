#ifndef QCORR_H
#define QCORR_H

#include <QtGui/QMainWindow>
#include "../ui_qcorr.h"   // UIC is always spiting out this form header files on the root of the project folder
#include "imgLabel.h"
#include "targetImgLabel.h"
#include "corrmethod.h"
#include "controlswindow.h"

class QImage;
class QPainter;
class QSize;
class QPoint;
class QString;
class QActionGroup;
#include <QtCore/QVector>
#include <QtGui/QRgb>

/** @ingroup classes */
/** @{ */
/** @defgroup qcorr_mainwindow Qcorr

 @class Qcorr "src/qcorr.h"

 @ingroup qcorr_mainwindow

 @brief A Digital Image Correlation Program (Template Matching and Pixel Disparity Finder) implemented in QT4

 This class combines all other sub-classed QWidgets implemented throughout the program. The main correlation used in the "Template matching" and "Disparity Finder" modes rely strongly in the functionality implemented in this class through the procedure convertToGrayScaleFloat()

 @note Correlation is performed on gray-scale (1 channel image) that are computed in this procedure through the convertToGrayScaleFloat() function.

 @par  Compile-time dependencies
    - The QT4 Framework
    - g++

 @bug
    - Perhaps a few around the rubberBand functionality, and others not noticed yet.

 @todo
    - Use pyramids method for faster correlation
    - Better disparity map implementation
    - Spacebar opens full screen mode on image.

 @authors Carlos Jaramillo
 @authors Joel Gonzalez

 */
/** @} */

class Qcorr : public QMainWindow, private Ui::QcorrClass
{
   Q_OBJECT

   public:
      Qcorr(QWidget *parent = 0); ///< Constructor of the Qcorr class
      ~Qcorr(); ///< Destructor: House keeping that should be done when the Qcorr main window is closed -- specifically, it closes the controlsWindow;

   private Q_SLOTS:
      void
      closeWindows(); ///< Q_SLOT that closes the main Qcorr window and the controls Window;
      void
      showControlsWindow(); ///< Q_SLOT that shows the controls window and raises it to the foreground if already open.
      void
      browseLeftImage(); ///< Q_SLOT that allows to browse and load an image on the left panel
      void
      browseRightImage();///< Q_SLOT that allows to browse and load an image on the right panel
      void
      changeMouse(); ///< Q_SLOT used to change the mouse pointer according to the current operation mode
      void
      viewMap(); ///< Q_SLOT that selectively provides the appropriate existent map of results from correlation (template matching) or pixel disparity
      void
      operate(); ///< Q_SLOT that starts the chosen operation according to the mode chosen, either template matching or disparity finder
      void
      abortOperation(); ///< Q_SLOT triggers the flag to abort the current operation

   private:
      /** ImgLabel
       * @brief  the ImgLabel class is a friend of Qcorr in order to make all members of Qcorr accessible by an ImgLabel object
       */
      friend class ImgLabel;

      /** ControlsWindow
       * @brief  allows to modify parameters for the correlation operations, such as template size and scan interval. This class is a friend of Qcorr.
       */
      friend class ControlsWindow;

      /** @brief  Displays any QImage on a Qlabel
       * @param image Pointer to a QImage instance
       * @param label Pointer to a QLabel instance
       */
      void
      displayImage(QImage *image, QLabel *label);

      /** @brief  Displays the reference image on the left panel's label. which is a sub-classed widget.
       * @param image Pointer to a QImage instance
       * @param label Pointer to a ImgLabel class instance
       */
      void
      displayImageLabel(QImage *image, ImgLabel *label);

      /** @brief  Sets up actions and Q_SIGNAL-Q_SLOT connections
       */
      void
      createActions();

      /** @brief  Enables/Disables operation modes actions related widgets
       * @param bEnable boolean flag to enable or disable the operation mode's actions widgets as well as the related widgets such as, start_pushButton and controls_pushButton
       */
      void
      setEnableActions(bool bEnable);

      /** @brief  Instantiates label widgets and initializes other member variables pertinent to the overall GUI functionality of the main window itself
       */
      void
      setImageLabels();

      void
      showEStop(); ///<  emergency stop to abort the disparity operation process

      void
      correlate(); ///< Performs template matching through correlation of the selected template against the target image. It calls findCorrelation() with the appropriate parameters to do a single template correlation across the entire target image.
      void
      disparity(); ///< Pixel-disparity finding operation. It should be mainly be used with stereo images that can get correlated row-by-row by using findCorrelation() with the pertinent parameters and the appropriate Q_SLOT function implementation.

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
       * @param rnDx x-coordinate where the highest level of correlation match is found (top-left corner of the match)
       * @param rnDy y-coordinate where the highest level of correlation match is found (top-left corner of the match)
       * @param nMethod Determines the selected method to be used in the correlation process. The method is a globally defined enumeration.
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
       *        Remark:
       *          The square root of the sum of the squares (RSS) is being used to
       *          calculate the aggregate accuracy of a measurement when the accuracies of the all the measuring devices are known.
       *          The average accuracy is not merely the arithmetic average of the accuracies (or uncertainties), nor is it the sum of them.
       *          Note how the RSS result in this case is greater than the largest of the values under the radical.
       *
       * @param bMultires Determines if multiresolution correlation should be applied, by making use of image pyramids.
       *                 With multiresoltion, the correlation can be determined faster than direct correlation.
       *                 Default is false.
       * @param nInitialXPosition Indicates the x-coordinate of the pixel on the target image where correlation should start. Default is 0
       * @param nInitialYPosition Indicates the y-coordinate of the pixel on the target image where correlation should start. Default is 0
       * @param nNumberOfRows Indicates the number of rows on the target image to be scanned. Default is 0, which means all of them.
       * @returns a float array resulting from the conversion of the source image into an 8-bit gray-scale image.
       */
      float
      findCorrelation(const unsigned char * imgTarget, const int nWI,
            const int nHI, const int nDepthI,
            const unsigned char * imgTemplate, const int nWT, const int nHT,
            const int nDepthT, int &rnDx, int &rnDy, int nMethod,
            bool bMultires = false, int nInitialXPosition = 0,
            int nInitialYPosition = 0, int nNumberOfRows = 0);

      /** @brief  Cast images to an 8-bit gray-scale channel of type float
       * @param pchImgOriginalBits Buffer of unsigned characters as the source image
       * @param nSize Number of pixels in the source image
       * @param nDepth Pixel depth of the source image
       * @returns the correlation number computed by method (directly).
       *           Additionally, the (dx,dy) offset of the template for which there exists a best match.
       */
      float *
      convertToGrayScaleFloat(const unsigned char * pchImgOriginalBits,
            int nSize, int nDepth);

      void
      updateStatusLabelWithDisparityInfo(); ///< Updates Status Bar with Information about parameters for the disparity operation

      /** @brief Used for testing and investing the bits stored in QImages or other Qt Widgets.
       * @param fileName a QString reference to the file-name as which the raw bits will be storedpchImgOriginalBits Buffer of unsigned characters as the source image
       * @returns true if the bits were properly dumped to the specified fileName
       */
      bool
      fileDumpQImage(const QString &fileName);

      int m_nXCorrelationCoordinate; ///< the resulting x-coordinate match obtained from correlation of a template against a target
      int m_nYCorrelationCoordinate; ///< the resulting y-coordinate match obtained from correlation of a template against a target

      CorrMethod *m_corrMethodDialog; ///< Dialog Box to choose a correlation method
      ControlsWindow *m_controlsWindow; ///< Dialog Box to modify correlation parameters such as template size and scan interval
      QString initialName; ///< String that saves the path for the first file image that has been loaded
      QImage *m_leftImage; ///< Left Panel's Image (a.k.a. "reference image" when performing template matching through correlation)
      QImage *m_rightImage; ///< Right Panel's Image (a.k.a "target image")
      QImage *m_templateImage; ///< Template Image that is selected from the reference image (in the left panel) that will be matched against
      QImage *m_corrMapImage; ///< Correlation Map resulting from the Template Matching action
      QImage *m_disparityMapImage; ///< Disparity Map that results from the pixel disparities found between the left and right images
      ImgLabel *m_leftImage_label; ///< label used to display the left image. This is sub-classed widget implemented with the functionality of allowing template selection by a rectangular rubber-band
      TargetImgLabel *m_targetImage_label; ///< a sub-classed label widget implemented with the purpose of displaying the target image in the right panel with added functionality such as the visualization of the found match
      QLabel *m_status_label; ///< status label that updates the mouse-pointer's position coordinates as it moves and selects templates. It also provides other types of information when required.

      QVector<QRgb> *m_grayColorTab; ///< 8-bit gray-scale color table
      QVector<QRgb> *m_greenColorTab; ///< 8-bit green-scale color table

      QPoint m_matchingPoint; ///< upper-left corner point where the correlation match was found
      QSize m_templateSize; ///< the current template's size as a QSize object
      QActionGroup *modes_actionGroup; ///< group of menu actions for the mode of operation.

      QDialogButtonBox *m_eStopDialog; ///< A dialogue to stop the current correlation process

      bool m_bHasLeftImage; ///< indicates that an image is loaded in the left panel
      bool m_bHasRightImage; ///< indicates that an image is loaded in the right panel
      bool m_bHasCorrMap; ///< indicates that a correlation map exists
      bool m_bHasDisparityMap; ///< indicates that a disparity map exists
      bool m_bEstop; ///< emergency stop for the
      int m_nScanInterval; ///< interval of scan traversal by the template
};


#endif // QCORR_H
