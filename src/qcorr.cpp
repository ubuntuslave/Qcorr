#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <QRubberBand>
#include "qcorr.h"
#include "globals.h"

Qcorr::Qcorr(QWidget *parent) :
   QMainWindow(parent)
{
   setupUi(this);

   setImageLabels();

   createActions();

   this->setWindowTitle(tr("QCorr"));
   this->setCentralWidget(main_frame); // Necessary for main frame to resize with main window
   //   resize(500, 400);
}

Qcorr::~Qcorr()
{
   // House keeping that should be done when the Qcorr main window is closed
   m_controlsWindow->close();
}

void
Qcorr::setImageLabels()
{
   m_leftImage_label = new ImgLabel(this);
   //   m_leftImage_label->setBackgroundRole(QPalette::Base);
   m_leftImage_label->setBackgroundRole(QPalette::Dark);
   m_leftImage_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
   m_leftImage_label->setScaledContents(true);
   m_leftImage_label->setMouseTracking(true);

   leftImage_scrollArea->setWidget(m_leftImage_label);
   leftImage_scrollArea->setBackgroundRole(QPalette::Dark);

   m_targetImage_label = new TargetImgLabel(this); // Draw Right Image
   //   rightImage_label->setBackgroundRole(QPalette::Base);
   m_targetImage_label->setBackgroundRole(QPalette::Dark);
   m_targetImage_label->setSizePolicy(QSizePolicy::Ignored,
         QSizePolicy::Ignored);
   m_targetImage_label->setScaledContents(true);

   rightImage_scrollArea->setWidget(m_targetImage_label);
   rightImage_scrollArea->setBackgroundRole(QPalette::Dark);

   // set flags for load-status of images and maps
   m_bHasLeftImage = false;
   m_bHasRightImage = false;
   m_bHasCorrMap = false;
   m_bHasDisparityMap = false;

   // BEGIN Status label configuration: vvvvvvvvv
   m_status_label = new QLabel;
   m_status_label->setAlignment(Qt::AlignLeft);
   QFont font;
   font.setFamily(QString::fromUtf8("Arial"));
   m_status_label->setFont(font);

   QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   sizePolicy.setHorizontalStretch(0);
   sizePolicy.setVerticalStretch(0);
   m_status_label->setSizePolicy(sizePolicy);

   statusbar->addWidget(m_status_label);
   // END Status label configuration ^^^^^^

   // This buttons should be initially disabled because there's no target image to correlate to
   start_pushButton->setEnabled(false);
   controls_pushButton->setEnabled(false);

   // Create Correlation Method Dialog, which is initially hidden
   m_corrMethodDialog = new CorrMethod(this);

   // Create Controls Window, which is initially hidden
   m_controlsWindow = new ControlsWindow(this);

   modes_actionGroup = new QActionGroup(menu_Mode);
   modes_actionGroup->addAction(actionTemplate_Matching);
   modes_actionGroup->addAction(action_Disparity_Finder);
   actionTemplate_Matching->setChecked(true);

   // Color Tables:
   // Gray-scale Color Table
   m_grayColorTab = new QVector<QRgb> (256); // for an 8-bit scale color table
   QVector<QRgb> fillerGrayColorTab(256);
   for (int i = 0; i <= 255; i++)
      {
         fillerGrayColorTab[i] = qRgb(i, i, i); // For a gray-scale color table
      }
   *m_grayColorTab = fillerGrayColorTab;

   // Green-scale Color Table
   m_greenColorTab = new QVector<QRgb> (256); // for an 8-bit scale color table
   QVector<QRgb> fillerGreenColorTab(256);
   for (int i = 0; i <= 255; i++)
      {
         fillerGreenColorTab[i] = qRgb(0, i, 0); // For a green-scale color table
      }
   *m_greenColorTab = fillerGreenColorTab;

   // eStop Dialog:
   m_eStopDialog = new QDialogButtonBox(this);
   m_eStopDialog->addButton(QDialogButtonBox::Abort);
   m_eStopDialog->setCenterButtons(true);
   m_eStopDialog->close();
   m_bEstop = false; // Intialize m_bEstop flag to false
}

// Set dialog's position on window
void
Qcorr::showEStop()
{
   // eStop Dialog:
   m_bEstop = false; // Allows this operation to proceed until it changes via the Abort QDialog

   int w = this->width();
   int h = this->height();
   int x = (this->width() - w) / 2;
   int y = (this->height() - h) / 2;
   m_eStopDialog->setGeometry(x, y, w, h);

   m_eStopDialog->show(); // Pops-up the Abort Dialogue
   m_eStopDialog->raise();
}

void
Qcorr::createActions()
{
   connect(quit_pushButton, SIGNAL(clicked()), this, SLOT(closeWindows()));
   connect(leftBrowse_pushButton, SIGNAL(clicked()), this,
         SLOT(browseLeftImage()));
   connect(rightBrowse_pushButton, SIGNAL(clicked()), this,
         SLOT(browseRightImage()));
   connect(start_pushButton, SIGNAL(clicked()), this, SLOT(operate()));
   connect(controls_pushButton, SIGNAL(clicked()), this,
         SLOT(showControlsWindow()));

   action_Quit->setShortcut(tr("Ctrl+Q"));
   connect(action_Quit, SIGNAL(triggered()), this, SLOT(close()));

   // View menu:
   connect(action_Map, SIGNAL(triggered()), this, SLOT(viewMap()));

   // Mode menu:
   connect(actionTemplate_Matching, SIGNAL(triggered()), this,
         SLOT(changeMouse()));
   connect(action_Disparity_Finder, SIGNAL(triggered()), this,
         SLOT(changeMouse()));

   // eStop QDialogAction
   connect(m_eStopDialog, SIGNAL(rejected()), this, SLOT(abortOperation()));

}
void
Qcorr::abortOperation()
{
   m_bEstop = true; // Break disparity process
   m_eStopDialog->close();
}

void
Qcorr::setEnableActions(bool bEnable)
{
   this->changeMouse();
   start_pushButton->setEnabled(bEnable);

   // Controls related:
   controls_pushButton->setEnabled(bEnable);

   actionTemplate_Matching->setEnabled(bEnable);
   action_Disparity_Finder->setEnabled(bEnable);
}

// begin Q_SLOTS vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void
Qcorr::showControlsWindow()
{
   m_controlsWindow->show();
   m_controlsWindow->raise(); // the widget will be visually in front of any overlapping widgets
}

void
Qcorr::closeWindows()
{
   emit this->close();
   m_controlsWindow->close();
}

void
Qcorr::browseLeftImage()
{
   if (leftImage_lineEdit->text().isEmpty())
      initialName = rightImage_lineEdit->text(); // observes the path on the other panel
   else
      initialName = leftImage_lineEdit->text(); // observes its own path


   if (initialName.isEmpty())
      initialName = QDir::homePath();

   QString fileName = QFileDialog::getOpenFileName(this, tr("Choose File"),
         initialName);
   fileName = QDir::toNativeSeparators(fileName);

   if (!fileName.isEmpty())
      {

         leftImage_lineEdit->setText(fileName);
         m_leftImage = new QImage(fileName);

         if (m_leftImage->isNull())
            {
               QMessageBox::information(this, tr("QCorr"),
                     tr("Cannot load %1.").arg(fileName));
               return;
            }

         this->displayImageLabel(m_leftImage, m_leftImage_label); // Draw Left Image

         m_leftImage_label->setMouseTracking(true);
         m_leftImage_label->setFocusPolicy(Qt::ClickFocus);

         m_bHasLeftImage = true;

         if (m_bHasRightImage)
            setEnableActions(true);
      }
}

void
Qcorr::browseRightImage()
{
   if (rightImage_lineEdit->text().isEmpty())
      initialName = leftImage_lineEdit->text(); // observes the path on the other panel
   else
      initialName = rightImage_lineEdit->text(); // observes its own path

   if (initialName.isEmpty())
      initialName = QDir::homePath();

   QString fileName = QFileDialog::getOpenFileName(this, tr("Choose File"),
         initialName);
   fileName = QDir::toNativeSeparators(fileName);

   if (!fileName.isEmpty())
      {

         rightImage_lineEdit->setText(fileName);
         m_rightImage = new QImage(fileName);

         if (m_rightImage->isNull())
            {
               QMessageBox::information(this, tr("QCorr"),
                     tr("Cannot load %1.").arg(fileName));
               return;
            }

         m_targetImage_label->setImage(*m_rightImage);

         m_bHasRightImage = true;

         if (m_bHasLeftImage)
            {
               setEnableActions(true);
               action_Map->setChecked(false); // So the image we're openning can be shown
               viewMap();
            }

         // CARLOS: just for testing:
         // To verify if the data has been converted to grayscale,
         // and that QImage's bits() function uses only the data pixels without any formatting headers
         //      m_grayRightImage = new QImage(convertToGrayScale(m_rightImage));
         //
         //      std::cout << "Original Image depth: " <<  m_rightImage->depth() << "-bit" << std::endl;
         //      std::cout << "Gray Scale Image depth: " <<  m_grayRightImage->depth() << "-bit" << std::endl;
         //      std::cout << "Number of Bytes: " << m_grayRightImage->numBytes() << "\tNumber of Colors: " << m_grayRightImage->numColors() << std::endl;
         //
         //      m_targetImage_label->setImage(*m_grayRightImage);
         //
         //        if(!fileDumpQImage(fileName + ".txt"))
         //            return;

         update();
      }
}

void
Qcorr::changeMouse()
{
   if (actionTemplate_Matching->isChecked())
      {
         m_leftImage_label->setSelectable(true);
         m_targetImage_label->setImage(*m_rightImage); // Present a Clean Image
         // Don't clear previous results just here in case we're curious about finding the highest disparity pixel through this mode
         //         this->corrResults_label->clear();   // Clear any results from a "Disparity Finder" operation
         m_controlsWindow->setEnableSpinBoxes(false); // Disable control spinBoxes because the following thorough correlation doesn't need them

         if (m_bHasCorrMap)
            {
               action_Map->setEnabled(true);
               emit this->viewMap();
            }
         else
            action_Map->setEnabled(false);
      }
   else if (action_Disparity_Finder->isChecked())
      {
         m_leftImage_label->setSelectable(false);
         m_targetImage_label->eraseEnclosedMatch();
         m_targetImage_label->setImage(*m_rightImage); // Present a Clean Image
         // Don't clear previous results here just in case we're curious about finding the highest disparity pixel through this mode
         //         this->corrResults_label->clear();    // And clear any results from a "Template Matching" operation

         m_controlsWindow->setEnableSpinBoxes(true); // Enable spinBoxes and specigy maximum values according to m_rightImage's size

         updateStatusLabelWithDisparityInfo();

         if (m_bHasDisparityMap)
            {
               action_Map->setEnabled(true);
               emit this->viewMap();
            }
         else
            action_Map->setEnabled(false);
      }
}

void
Qcorr::viewMap()
{

   if (actionTemplate_Matching->isChecked() && action_Map->isChecked())
      {
         // Display Correlation Level Map over Right Panel's Image
         //       offset the correlation map's position by half the height and width of the template
         //       so it's center around the matching area instead of being at the top-left corner of it
         m_targetImage_label->overlayImage(*m_corrMapImage,
               m_templateSize.width() / 2, m_templateSize.height() / 2);
      }
   else if (action_Disparity_Finder->isChecked() && action_Map->isChecked())
      {
         m_targetImage_label->setImage(*m_disparityMapImage); // Display Disparity Map on the Right Panel
      }
   else
      {
         m_targetImage_label->setImage(*m_rightImage); // Display Right Image
      }
}

void
Qcorr::operate()
{

   if (actionTemplate_Matching->isChecked())
      {
         correlate();
      }

   // Otherwise, perform other Action: Disparity Finder:
   if (action_Disparity_Finder->isChecked())
      {
         disparity();
      }

}

// end Q_SLOTS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


void
Qcorr::correlate()
{
   if (m_leftImage_label->m_rubberBand->isVisible())
      {
         m_templateImage = new QImage(m_leftImage->copy(
               m_leftImage_label->m_rubberBand->geometry()));

         m_templateSize = m_templateImage->size();

         m_corrMethodDialog->exec(); // Making sure that this dialog behaves modally
         // Otherwise, a dialog is not modal if it's invoked using show()

         if (m_corrMethodDialog->getMethod() == N0_CORR_METHOD)
            {
               if (!m_leftImage_label->m_rubberBand->isVisible())
                  m_targetImage_label->eraseEnclosedMatch();
            }
         else
            {
               this->corrResults_label->clear(); // Clear any results from a "Disparity Finder" operation
               m_bHasCorrMap = false; // Allow to create a new correlation map

               showEStop(); // Set dialog's position on window and reset m_bEstop flag to false

               // Target Image dimensions:
               int wI = m_rightImage->width();
               int hI = m_rightImage->height();
               int depthI = m_rightImage->depth();

               // Template Image dimensions:
               int wT = m_templateImage->width();
               int hT = m_templateImage->height();
               int depthT = m_templateImage->depth();

               QApplication::setOverrideCursor(Qt::WaitCursor);

               float fCorrLevel = findCorrelation(m_rightImage->bits(), wI, hI,
                     depthI, m_templateImage->bits(), wT, hT, depthT,
                     m_nXCorrelationCoordinate, m_nYCorrelationCoordinate,
                     m_corrMethodDialog->getMethod(), false);
               QApplication::restoreOverrideCursor();

               m_bHasCorrMap = true;

               // CARLOS: just for testing:
               //         m_targetImage_label->setImage(*m_templateImage);   // Draw Template on Right Label
               //
               //         this->m_status_label->setText(
               //               "Finding Correlation for the <b>(" + QString::number(m_templateImage->width()) + "x"
               //               + QString::number(m_templateImage->height()) + ")px </b>Template ..." );


               // Validate the results before allowing to draw the enclosing rectangle around the match
               if (fCorrLevel >= 0.0 && !m_bEstop)
                  {
                     m_targetImage_label->setImage(*m_rightImage); // reset Image

                     m_matchingPoint.setX(m_nXCorrelationCoordinate);
                     m_matchingPoint.setY(m_nYCorrelationCoordinate);
                     m_targetImage_label->drawEnclosedMatch(m_matchingPoint,
                           m_templateSize);

                     this->corrResults_label->setText("Correlation level: <b>"
                           + QString::number(fCorrLevel) + "</b>\tat <b>("
                           + QString::number(m_nXCorrelationCoordinate) + ", "
                           + QString::number(m_nYCorrelationCoordinate)
                           + ")px</b>");
                     action_Map->setEnabled(true);
                     emit this->viewMap(); // emit this signal so it refreshes the correlation map automatically

                  }
               else
                  m_targetImage_label->eraseEnclosedMatch();

               m_eStopDialog->close();
            }
      }
   else
      {
         this->m_status_label->setText("There is No template!");
         this->corrResults_label->clear();
      }
}

void
Qcorr::disparity()
{
   QApplication::setOverrideCursor(Qt::WaitCursor);

   showEStop(); // Set dialog's position on window and reset m_bEstop flag to false

   this->corrResults_label->clear(); // And clear any results from a "Template Matching" operation

   m_templateImage = new QImage(); // Create instance of template image

   m_nScanInterval = m_controlsWindow->getScanInterval();
   m_templateSize.setHeight(m_controlsWindow->getTemplateSize());
   m_templateSize.setWidth(m_controlsWindow->getTemplateSize());

   // Target Image dimensions:
   int wI = m_rightImage->width();
   int hI = m_rightImage->height();
   int depthI = m_rightImage->depth();

   // Template Image dimensions:
   int wT = m_templateSize.width();
   int hT = m_templateSize.height();
   int depthT = m_leftImage->depth();

   // Traverse a number of times determined by the number of intervals that fit on the target image
   int nXTraverse = ((wI - wT) / m_nScanInterval) - 1; // must substract one from this value, so it doesn't go beyond the margins
   int nYTraverse = ((hI - hT) / m_nScanInterval) - 1; // must substract one from this value, so it doesn't go beyond the margins;

   // Store the disparities along the rows of pixels
   int nDispArraySize = nXTraverse * nYTraverse;
   int *anDisparityXValues = new int[nDispArraySize]; // Array to save the disparity values for each pixel

   unsigned char * achRightImage_bits = m_rightImage->bits();

   QPoint templateCoordsPoint;

   QImage *resultImage = new QImage(nXTraverse, nYTraverse,
         QImage::Format_Indexed8); // Empty Image
   // For now, using only gray-scale color table
   resultImage->setColorTable(*m_greenColorTab);

   m_leftImage_label->m_rubberBand->show(); // to visualize the template traversal

   updateStatusLabelWithDisparityInfo();

   int nPixelDisparity; // used to temporarily store the disparity result from each iteration
   int nIndexYOffset; // Used to save up recalculation of y-index offset for each row
   float fCorrLevel; // to temporarily store the strongest level of correlation
   int nMaxDisparity = 0; // To store the highest pixel-disparity found
   // and location coordinates
   int nMaxDispXcoord = 0;
   int nMaxDispYcoord = 0;

   // Traverse the template of the reference (left) and target(right) images with respect to rows only
   // The template traverses an entire row, and then a new template at the next pixel is created and traversed on the raw
   // This process repeats for all the pixels in the row, and then correlate the next row's pixels in the same fashion.
   for (int y = 0, yIndex = 0; y < nYTraverse; y++, yIndex += m_nScanInterval) // Traverses the height until the template's bottom is sitting on the bottom edge of the target
      { // visit rows
         m_nXCorrelationCoordinate = 0; // Reset to 0 at the beginning of each row
         fCorrLevel = 0.0; // Clear correlation level
         nIndexYOffset = y * nXTraverse;
         for (int x = 0, xIndex = 0; x < nXTraverse; x++, xIndex
               += m_nScanInterval) // Traverses a row of the target
            { // visit columns

               if (m_bEstop)
                  break; // Emergency break
               // Set template coordinates
               templateCoordsPoint.setX(xIndex);
               templateCoordsPoint.setY(yIndex);
               // Draw rubber band and match rectangle to indicate current template correlation
               // to visualize the template traversal across the images
               m_leftImage_label->m_rubberBand->setGeometry(QRect(
                     templateCoordsPoint, m_templateSize));
               m_targetImage_label->drawEnclosedMatch(templateCoordsPoint,
                     m_templateSize);

               // Extract current template image
               *m_templateImage = m_leftImage->copy(
                     m_leftImage_label->m_rubberBand->geometry());

               qApp->processEvents(QEventLoop::DialogExec); // Stay Responsive


               // the next correlation position on the line has to pay attention to the correlation level return,
               // so when the previous match is not perfect (in this case 1.0), the line should be scanned from the beginning
               if (fCorrLevel < 0.9)
                  m_nXCorrelationCoordinate = 0; // The previous template matching was not perfect, so start from the beginning of the row

               fCorrLevel = findCorrelation(achRightImage_bits, wI, hI,
                     depthI, // force to correlate 1 row of the height of the template
                     m_templateImage->bits(), wT, hT, depthT,
                     m_nXCorrelationCoordinate, m_nYCorrelationCoordinate, // don't care about the vertical coordinates
                     CORR_COEFF, // correlation method
                     // CROSS_CORR, // correlation method
                     false, m_nXCorrelationCoordinate, yIndex, 1); // in order to save time,
               // nInitialXPosition can be the previously matched pixel


               // Store disparity of current pixel in question
               nPixelDisparity = xIndex - m_nXCorrelationCoordinate;
               if (nPixelDisparity < 0) // below an average match (value is arbitrarily chosen)
                  {
                     nPixelDisparity = 0;
                  }

               //         std::cout << "Xl=" << xIndex << ":" << "Xr=" << m_nXCorrelationCoordinate << "Yr=" << m_nYCorrelationCoordinate << " : ";

               anDisparityXValues[nIndexYOffset + x] = nPixelDisparity;

               if (nPixelDisparity > nMaxDisparity)
                  {
                     nMaxDisparity = nPixelDisparity; // Keep track of highest pixel-disparity value
                     // and location coordinates:
                     nMaxDispXcoord = m_nXCorrelationCoordinate;
                     nMaxDispYcoord = m_nYCorrelationCoordinate;
                  }

            }
      }

   // Clean up enclosing visualizations of template traversal
   m_targetImage_label->eraseEnclosedMatch();
   m_leftImage_label->m_rubberBand->hide();

   if (!m_bEstop && !(resultImage->isNull()))
      {
         // Display Maximum Disparity found and Coordinates of such point
         this->corrResults_label->setText("Highest Disparity Found: <b>"
               + QString::number(nMaxDisparity) + "px</b>\tat <b>("
               + QString::number(nMaxDispXcoord) + ", " + QString::number(
               nMaxDispYcoord) + ")px</b>");

         // Enclosed template of highest disparity
         m_matchingPoint.setX(nMaxDispXcoord);
         m_matchingPoint.setY(nMaxDispYcoord);
         m_targetImage_label->drawEnclosedMatch(m_matchingPoint, m_templateSize);

         // Normalize disparity values and store them in result Image:
         for (int y = 0; y < nYTraverse; y++) // Traverses the height
            { // visit rows
               nIndexYOffset = y * nXTraverse;
               for (int x = 0; x < nXTraverse; x++) // Traverses a row of the target
                  { // visit columns
                     // Normalize disparity value from 0 to 255, based on maximum disparity being the width of the Image
                     // equation used:
                     //  x = 255 - (255(wI - disp)/wI)
                     anDisparityXValues[nIndexYOffset + x] = 255 - (255 * (wI
                           - anDisparityXValues[nIndexYOffset + x]) / wI);
                     resultImage->setPixel(x, y,
                           anDisparityXValues[nIndexYOffset + x]);
                  }
            }

         for (int i = 0; i < nDispArraySize; i++)
            {
               std::cout << anDisparityXValues[i] << " : ";
               //         qDebug() << anDisparityXValues[i] << " : ";
            }
         // Draw disparity map:
         // The smaller result disparity image gets scaled uniformly to the width and height of the original reference image
         m_disparityMapImage = new QImage(resultImage->scaledToWidth(wI,
               Qt::SmoothTransformation));
         *m_disparityMapImage = m_disparityMapImage->scaledToHeight(hI,
               Qt::SmoothTransformation);
         // ^^^^ either Qt::FastTransformation or Qt::SmoothTransformation
         m_bHasDisparityMap = true;

         // Draw disparity map:
         action_Map->setChecked(true);
         action_Map->setEnabled(true);
         emit
         this->viewMap(); // emit this signal so it refreshes the correlation map automatically

         m_eStopDialog->close();
      }

   QApplication::restoreOverrideCursor();

}

float
Qcorr::findCorrelation(const unsigned char * imgTarget, const int nWI,
      const int nHI, const int nDepthI, const unsigned char * imgTemplate,
      const int nWT, const int nHT, const int nDepthT, int &rnDx, int &rnDy,
      int nMethod, bool bMultires, int nInitialXPosition,
      int nInitialYPosition, int nNumberOfRows)
{
   // Helped to test that the bits dumped by QImage's bits() function
   // is the actual data (pixels) of the image without any header.
   // ...just pure pixel data!
   //   QFile file("test");  // in the executable application's folder
   //   if (!file.open(QIODevice::WriteOnly)) {
   //      QMessageBox::warning(this, tr("QCorr Image"),
   //            tr("Cannot write file %1:\n%2.")
   //            .arg(file.fileName())
   //            .arg(file.errorString()));
   //      return false;
   //   }
   //   QDataStream out(&file);
   //   out.setVersion(QDataStream::Qt_4_5);
   //
   //   QApplication::setOverrideCursor(Qt::WaitCursor);
   //
   //   // Helped to test that the bits dumped by QImage's bits() function
   //   // is the actual data (pixels) of the image without any header.
   //   // ...just pure pixel data!
   ////   const unsigned char * imgTarget = m_grayRightImage->bits();
   //
   //   int mysalt = 0;  // just to see if the image has extra bytes that might be missing
   //   int imgBytes = m_grayRightImage->numBytes() + mysalt;
   //
   //   for (int byteN = 0; byteN < imgBytes; ++byteN) {
   ////      out << quint8(imgTarget[byteN]);
   //      out << quint8(imgTarget[byteN]);
   //   }

   int i, j, k, n, x, y, total;
   int nXTraverse, nYTraverse, mxlevel, lowres;
   int nPixelNumber;
   float fSumTop, fSumBottom, fDiff, fCorr;
   float fAverage, fTemplatePower, fTargetPower;
   float *pfImgTarget, *pfImgTemplate, *pfTraversedTarget,
         *pfTraversingTemplate;
   //float mag
   float fMin, fMax;
   //   double dXSize, dYSize;


   //   QImage II1, II2, Ifft1, Ifft2, Iblur, pyramidTarget[8], pyramidTemplate[8];
   //   QImage Ifft1, Ifft2, Iblur, pyramidTarget[8], pyramidTemplate[8];

   // Images' size:
   int sizeI = nWI * nHI;
   int sizeT = nWT * nHT;

   /* error checking: size of pfTraversedTarget I1 must be >= than pfTraversingTemplate I2 */
   if ((nWT > nWI) || (nHT > nHI))
      {
         QMessageBox::warning(this, tr("QCorr"), tr(
               "Traversed Target Image is smaller than Traversing Template\n"));
         QApplication::restoreOverrideCursor();
         return 0.;
      }

   // cast images to an 8-bit channel (convert them to gray-scale images) as floats:
   float *afImgTarget = convertToGrayScaleFloat(imgTarget, sizeI, nDepthI);

   float *afImgTemplate = convertToGrayScaleFloat(imgTemplate, sizeT, nDepthT);

   /*
    * create pfTraversedTarget and pfTraversingTemplate pyramids with original images at base;
    * if no multiresolution is used, pyramids consist of only one level.
    */
   //   pyramidTarget[0] = *m_grayRightImage; // base: original traversed target
   //   pyramidTemplate[0] = *m_templateImage; // base: original traversing template

   // CARLOS: needs review from this point on... (and perhaps above, also) vvvvvvvvvvvvvv

   if (bMultires)
      {
         /* set lowest resolution for pyramidTarget (empirically tested) */
         switch (nMethod)
            {
            case CROSS_CORR:
            case SUM_SQ_DIFF:
               lowres = 64;
               break;
            case CORR_COEFF:
               lowres = 128;
               break;
               //            case PHASE_CORR:
               //               lowres = MAX(nWI, nHI); /* disable bMultires */
               //               break;
            }

         /* update lowres if pyramidTemplate will become too small  */
         for (k = 1; (nWI >> k) >= lowres && (nHI >> k) >= lowres; k++)
            ;
         for (k--; (nWT >> k) < 4 || (nHT >> k) < 4; k--)
            lowres *= 2;

         /* compute lower-res versions for remaining pyramid levels */
         for (k = 1; (nWI >> k) >= lowres && (nHI >> k) >= lowres; k++)
            {
               //               pyramidTarget[k] = m_grayRightImage->scaled(nWI, nHI,)


               //               pyramidTarget[k] = NEWIMAGE;
               //               pyramidTemplate[k] = NEWIMAGE;
               //// !!!!!!!!!!
               //               // CARLOS: The resize must be done with a function (Perhaps, OpenCV)
               //               IP_resize(pyramidTarget[k - 1], nWI >> k, nHI >> k, TRIANGLE, pyramidTarget[k]);
               //               IP_resize(pyramidTemplate[k - 1], nWT >> k, nHT >> k, TRIANGLE,
               //                     pyramidTemplate[k]);
            }
         mxlevel = k - 1;
      }
   else
      mxlevel = 0;

   // Define the maximum width and height of the correlation area
   nXTraverse = (nWI - nWT) >> mxlevel; // >> means: shift bit (divide by 2*mxlevel times)
   if (nNumberOfRows == 0)
      nYTraverse = (nHI - nHT) >> mxlevel;
   else
      nYTraverse = nNumberOfRows - 1;
   // ---------------------------------------------
   // To be used to display a brightness map based on correlation values at each evaluated pixel
   if (!m_bHasCorrMap) // Don't destroy previous correlation image if existing
      m_corrMapImage = new QImage(nXTraverse + 1, nYTraverse + 1,
            QImage::Format_Indexed8);

   // If the image's format is either monochrome or 8-bit, the given index_or_rgb value must be an index in the image's color table
   m_corrMapImage->setColorTable(*m_grayColorTab);
   // Array size is correct based on the number of correlations to be performed on the target
   float *afCorrValues = new float[(nXTraverse - nInitialXPosition + 1)
         * (nYTraverse + 1)]; // Array to save results of each correlation operation at certain pixel
   //   float *afCorrValues = new float[(nXTraverse+1) * (nYTraverse+1)]; // Array to save results of each correlation operation at certain pixel
   int nCorrCounter = 0;
   uint nValue; // to paint the pixels of the correlation map image
   // ---------------------------------------------


   /* multiresolution correlation: use results of lower-res correlation
    * (at the top of the pyramid) to narrow the search in the higher-res
    * correlation (towards the base of the pyramid).
    */
   for (n = mxlevel; n >= 0; n--)
      {
         //         /* init vars based on pyramid at level n */
         //         nWI = pyramidTarget[n]->width;
         //         nHI = pyramidTarget[n]->height;
         //         nWT = pyramidTemplate[n]->width;
         //         nHT = pyramidTemplate[n]->height;

         /* pointers to pfTraversedTarget and pfTraversingTemplate data */
         //         pfImgTarget = (float *) pyramidTarget[n]->buf[0]; /* pfTraversedTarget    ptr */
         //         pfImgTemplate = (float *) pyramidTemplate[n]->buf[0]; /* pfTraversingTemplate ptr */
         pfImgTarget = afImgTarget; //[0]; /* pfTraversedTarget    ptr */
         pfImgTemplate = afImgTemplate; //[0]; /* pfTraversingTemplate ptr */

         /* init fMin and fMax */
         fMin = 10000000.;
         fMax = 0.;

         switch (nMethod)
            {
            case CROSS_CORR:
               /*  CROSS_CORR (cross correlation):
                *             C(u,v) = sum of {T(x,y) * I(x-u,y-v)}
                *                      --------------------------------
                *                      sqrt{ sum of {I(x-u,y-v)^2}}
                *     Levels:
                *             C = 1 Perfect Match
                *             0 < C < 1: Some Match (closer to 1 is higher)
                *             C = 0: No Match       *
                */

               // slide Template across the Target (pixel-by-pixel)
               for (y = 0; y <= nYTraverse; y++) // Traverses the height until the template's bottom is sitting on the bottom edge of the target
                  { // visit rows
                     if (m_bEstop)
                        break; // Emergency break
                     for (x = 0 + nInitialXPosition; x <= nXTraverse; x++) // Traverses the width until the template's right edge is on the right edge of the target
                        { // visit columns

                           qApp->processEvents(QEventLoop::DialogExec); // Stay Responsive
                           if (m_bEstop)
                              break; // Emergency break

                           fSumTop = fSumBottom = 0; // Clear sums to 0 for each Template-Target comparison

                           nPixelNumber = ((y + nInitialYPosition) * nWI) + x; // Start at desired pixel coordinates
                           pfTraversedTarget = pfImgTarget + nPixelNumber; // Points to current position in target float array
                           pfTraversingTemplate = pfImgTemplate; // Always begins pointing to upper-left corner of template float array

                           // pixel-by-pixel comparison loops:
                           // Comparing the Traversing Image's region (of Template Size) to the Template itself
                           for (i = 0; i < nHT; i++)
                              { // Similar to convolution
                                 for (j = 0; j < nWT; j++)
                                    {
                                       fSumTop += (pfTraversingTemplate[j]
                                             * pfTraversedTarget[j]);
                                       fSumBottom += (pfTraversedTarget[j]
                                             * pfTraversedTarget[j]);
                                    }
                                 pfTraversedTarget += nWI; // move to next row relative to Target
                                 pfTraversingTemplate += nWT; // move to next row in the Template
                              }

                           if (fSumBottom == 0)
                              continue;

                           fCorr = fSumTop / sqrt(fSumBottom);
                           if (fCorr > fMax)
                              {
                                 fMax = fCorr;
                                 rnDx = x;
                                 rnDy = y + nInitialYPosition;
                              }

                           // Also, keep track of the minimum correlation found (for mapping purposes)
                           if (fCorr < fMin)
                              {
                                 fMin = fCorr;
                              }

                           afCorrValues[nCorrCounter] = fCorr; // Save correlation value of this round

                           //                           std::cout << nCorrCounter << ": " << afCorrValues[nCorrCounter] << " | ";
                           nCorrCounter++;

                        } //next column
                     //                     std::cout << std::endl;
                  } //next row


               if (m_bEstop)
                  break; // Emergency break
               // update search window or normalize final correlation value

               if (n)
                  { // set search window for next pyramid level
                     //                     xI = MAX(0, 2 * rnDx - n);
                     //                     yI = MAX(0, 2 * rnDy - n);
                     //                     nXTraverse = MIN(2 * nWI, 2 * rnDx + n);
                     //                     nYTraverse = MIN(2 * nHI, 2 * rnDy + n);
                  }
               else
                  {
                     // normalize correlation value at final level
                     total = nWT * nHT;
                     for (i = fTemplatePower = 0; i < total; i++)
                        fTemplatePower += (pfImgTemplate[i] * pfImgTemplate[i]);

                     float fSquareRootOfTemplatePower = sqrt(fTemplatePower);
                     fCorr = fMax / fSquareRootOfTemplatePower;
                     //                  std::cout << "Max: " << fMax << "  TemplatePower: " << fTemplatePower;

                     // Normalize fMax and fMin
                     fMax = fCorr; // because it's already normalized
                     fMin = fMin / fSquareRootOfTemplatePower;

                     nCorrCounter = 0; // Reset nCorrCounter before it starts counting again

                     // Normalize all the correlation values stored in the array afCorrValues

                     if (!m_bHasCorrMap) // Don't destroy previous correlation image if existing
                        for (y = 0; y <= nYTraverse; y++) // Traverses the height until the template's bottom is sitting on the bottom edge of the target
                           { // visit rows
                              for (x = 0 + nInitialXPosition; x <= nXTraverse; x++) // Traverses the width until the template's right edge is on the right edge of the target
                                 { // visit columns
                                    // Normalized each correlation value in the array with respect to the sqrt(fTemplatePower)
                                    afCorrValues[nCorrCounter]
                                          = afCorrValues[nCorrCounter]
                                                / fSquareRootOfTemplatePower;

                                    // Interpolate values from 0 to 1 between fMin and fMax
                                    // x_normalized = (x - min) / (max - min)
                                    if (afCorrValues[nCorrCounter] < 0.0)
                                       afCorrValues[nCorrCounter] = 0.0;
                                    else
                                       afCorrValues[nCorrCounter]
                                             = (afCorrValues[nCorrCounter]
                                                   - fMin) / (fMax - fMin);

                                    //                           std::cout << nCorrCounter << ": " << afCorrValues[nCorrCounter] << " | ";

                                    // Paint pixel in gray-scale correlation map
                                    nValue = (int) (afCorrValues[nCorrCounter]
                                          * 255.0); // normalized correlation value for a grayscale
                                    m_corrMapImage->setPixel(x, y, nValue);
                                    nCorrCounter++;
                                 }
                              //                        std::cout << std::endl;
                           }
                  }
               break;

            case SUM_SQ_DIFF:
               /*  SUM_SQ_DIFF (sum of squared differences):
                *             C(u,v) = sum of {T(x,y)-I(x-u,y-v)}^2
                *                      ------------------------------
                *                      sqrt{ sum of {I(x-u,y-v)^2}}
                *     Levels:
                *             C = 0 Perfect Match
                *             0 < C < 1: Some Match (closer to 0 is higher)
                *             C = 1: No Match
                */
               for (y = 0; y <= nYTraverse; y++) // Traverses the height until the template's bottom is sitting on the bottom edge of the target
                  { // visit rows
                     for (x = 0 + nInitialXPosition; x <= nXTraverse; x++) // Traverses the width until the template's right edge is on the right edge of the target
                        { // slide window

                           qApp->processEvents(QEventLoop::DialogExec); // Stay Responsive
                           if (m_bEstop)
                              break; // Emergency break

                           fSumTop = fSumBottom = 0;

                           nPixelNumber = ((y + nInitialYPosition) * nWI) + x; // Start at desired pixel coordinates
                           pfTraversedTarget = pfImgTarget + nPixelNumber; // Points to current position in target float array

                           pfTraversingTemplate = pfImgTemplate;
                           for (i = 0; i < nHT; i++)
                              { // convolution
                                 for (j = 0; j < nWT; j++)
                                    {
                                       fDiff = pfTraversingTemplate[j]
                                             - pfTraversedTarget[j];
                                       fSumTop += (fDiff * fDiff);
                                       fSumBottom += (pfTraversedTarget[j]
                                             * pfTraversedTarget[j]);
                                    }
                                 pfTraversedTarget += nWI;
                                 pfTraversingTemplate += nWT;
                              }
                           if (fSumBottom == 0)
                              continue;

                           fCorr = fSumTop / sqrt(fSumBottom);
                           if (fCorr < fMin)
                              {
                                 fMin = fCorr;
                                 rnDx = x;
                                 rnDy = y + nInitialYPosition;
                              }

                           // Also, keep track of the maximum correlation found (for mapping purposes)
                           if (fCorr > fMax)
                              {
                                 fMax = fCorr;
                              }

                           afCorrValues[nCorrCounter] = fCorr; // Save correlation value of this round
                           nCorrCounter++;
                        } // next column
                  } // next row
               if (m_bEstop)
                  break; // Emergency break

               // update search window or normalize final correlation value
               if (n)
                  { /* set search window for next pyramid level  */
                     //                     xI = MAX(0, 2 * rnDx - n);
                     //                     yI = MAX(0, 2 * rnDy - n);
                     //                     nXTraverse = MIN(2 * nWI, 2 * rnDx + n);
                     //                     nYTraverse = MIN(2 * nHI, 2 * rnDy + n);
                  }
               else
                  { // normalize correlation value at final level
                     total = nWT * nHT;
                     for (i = fTemplatePower = 0; i < total; i++)
                        fTemplatePower += (pfImgTemplate[i] * pfImgTemplate[i]);
                     float fSquareRootOfTemplatePower = sqrt(fTemplatePower);
                     fCorr = fMin / fSquareRootOfTemplatePower;

                     // Normalize fMax and fMin
                     fMin = fCorr; // because it's already normalized
                     fMax = fMax / sqrt(fTemplatePower);

                     nCorrCounter = 0; // Reset nCorrCounter before it starts counting again

                     if (!m_bHasCorrMap) // Don't destroy previous correlation image if existing
                        // Normalize all the correlation values stored in the array afCorrValues
                        for (y = 0; y <= nYTraverse; y++) // Traverses the height until the template's bottom is sitting on the bottom edge of the target
                           { // visit rows
                              for (x = 0 + nInitialXPosition; x <= nXTraverse; x++) // Traverses the width until the template's right edge is on the right edge of the target
                                 { // visit columns
                                    // Normalized each correlation value in the array with respect to the sqrt(fTemplatePower)
                                    afCorrValues[nCorrCounter]
                                          = afCorrValues[nCorrCounter]
                                                / fSquareRootOfTemplatePower;

                                    // Interpolate values from 0 to 1 between fMin and fMax, where 0 in this case indicates a higher correlation level
                                    // x_normalized = [(min-x) / (max - min)] + 1
                                    afCorrValues[nCorrCounter] = ((fMin
                                          - afCorrValues[nCorrCounter]) / (fMax
                                          - fMin)) + 1;

                                    //                              std::cout << nCorrCounter << ": " << afCorrValues[nCorrCounter] << " | ";

                                    // Paint pixel in gray-scale correlation map
                                    nValue = (int) (afCorrValues[nCorrCounter]
                                          * 255.0); // normalized correlation value for a grayscale
                                    m_corrMapImage->setPixel(x, y, nValue);
                                    nCorrCounter++;
                                 }
                              //                           std::cout << std::endl;
                           }
                  }
               break;

            case CORR_COEFF:
               /* CORR_COEFF (correlation coefficient):
                *             C(u,v) = sum of {(T(x,y)-Tavg) * (I(x-u,y-v)-Iavg)}
                *                      -----------------------------------------------------
                *                      sqrt{sum{(T(x,y)-Tavg)^2} * sum{(I(x-u,y-v)-Iavg)^2}}
                *     Levels:
                *             C = 1 Perfect Match
                *             C = 0: No Match
                *             0 < C < 1: Some Match (closer to 1 is better)
                *             -1 < C < 0: Mismatch
                */

               // compute pfTraversingTemplate average
               total = nWT * nHT;
               for (i = fAverage = 0; i < total; i++)
                  fAverage += pfImgTemplate[i];
               fAverage /= total;

               // subtract average from template
               for (i = 0; i < total; i++)
                  pfImgTemplate[i] -= fAverage;

               // compute template power
               for (i = fTemplatePower = 0; i < total; i++)
                  fTemplatePower += (pfImgTemplate[i] * pfImgTemplate[i]);

               // CARLOS: this following averaging process of the Target Image is done next in a similar way as with the template
               //               /* compute local pfTraversedTarget average: blur with box filter */
               //               dXSize = nWT + !(nWT % 2); /* make filter width  odd */
               //               dYSize = nHT + !(nHT % 2); /* make filter height odd */
               //               IP_blur(pyramidTarget[n], dXSize, dYSize, Iblur = NEWIMAGE);
               //
               //               /* subtract local pfTraversedTarget averages from pixels */
               //               IP_subtractImage(pyramidTarget[n], Iblur, pyramidTarget[n]);
               //               IP_freeImage(Iblur);

               // compute average on the entire traversed target image
               //     Not sure if the average has to be taken from the whole image (or the traversed window)
               total = nWI * nHI;
               for (i = fAverage = 0; i < total; i++) // total is the same for both templates and target samples
                  fAverage += pfImgTarget[i];

               fAverage /= total;

               // subtract average on the traversed target image segment
               for (i = 0; i < total; i++)
                  pfImgTarget[i] -= fAverage;

               for (y = 0; y <= nYTraverse; y++)
                  { // visit rows

                     if (m_bEstop)
                        break; // Emergency break

                     for (x = 0 + nInitialXPosition; x <= nXTraverse; x++)
                        { // slide window
                           qApp->processEvents(QEventLoop::DialogExec); // Stay Responsive
                           if (m_bEstop)
                              break; // Emergency break

                           fSumTop = fSumBottom = fTargetPower = 0; // Reset sums

                           nPixelNumber = ((y + nInitialYPosition) * nWI) + x; // Start at desired pixel coordinates
                           pfTraversedTarget = pfImgTarget + nPixelNumber; // pfImage has been averaged out also

                           pfTraversingTemplate = pfImgTemplate; /* from pfTraversedTarget and pfTraversingTemplate */

                           // Points to current position in target float array

                           // compute average on the window of the traversed target image
                           // which is wrong because it must be the average of the whole image,
                           // so the following it's commented out!
                           //                     for (i = fAverage = 0; i < total; i++)  // total is the same for both templates and target samples
                           //                        fAverage += pfTraversedTarget[i];
                           //
                           //                     fAverage /= total;
                           //
                           //                     // subtract average on the traversed target image segment
                           //                     for (i = 0; i < total; i++)
                           //                        pfTraversedTarget[i] -= fAverage;

                           for (i = 0; i < nHT; i++)
                              { // convolution
                                 for (j = 0; j < nWT; j++)
                                    {
                                       fSumTop += (pfTraversingTemplate[j]
                                             * pfTraversedTarget[j]);
                                       fTargetPower += (pfTraversedTarget[j]
                                             * pfTraversedTarget[j]);
                                    }
                                 pfTraversedTarget += nWI;
                                 pfTraversingTemplate += nWT;
                              }

                           fSumBottom = fTargetPower * fTemplatePower;
                           fCorr = fSumTop / sqrt(fSumBottom);
                           if (fCorr > fMax)
                              {
                                 fMax = fCorr;
                                 rnDx = x;
                                 rnDy = y + nInitialYPosition;
                              }
                           // Also, keep track of the minimum correlation found (for mapping purposes)
                           if (fCorr < fMin)
                              {
                                 fMin = fCorr;
                              }

                           afCorrValues[nCorrCounter] = fCorr; // Save correlation value of this round
                           //                     std::cout << nCorrCounter << ": " << afCorrValues[nCorrCounter] << " | ";
                           nCorrCounter++;
                        } // next column
                  } // next row

               if (m_bEstop)
                  break; // Emergency break

               // update search window or set final correlation value
               if (n)
                  { // set search window for next pyramid level
                     //                  xI = MAX(0, 2 * rnDx - n);
                     //                  yI = MAX(0, 2 * rnDy - n);
                     //                  nXTraverse = MIN(2 * nWI, 2 * rnDx + n);
                     //                  nYTraverse = MIN(2 * nHI, 2 * rnDy + n);
                  }
               else
                  { // set correlation value at final level
                     fCorr = fMax;

                     nCorrCounter = 0; // Reset nCorrCounter before it starts counting again

                     if (!m_bHasCorrMap) // Don't destroy previous correlation image if existing
                        // The correlation values stored in the array afCorrValues are already normalized
                        // there is no need to divide by the square root of the powers
                        for (y = 0; y <= nYTraverse; y++) // Traverses the height until the template's bottom is sitting on the bottom edge of the target
                           { // visit rows
                              for (x = 0 + nInitialXPosition; x <= nXTraverse; x++) // Traverses the width until the template's right edge is on the right edge of the target
                                 { // visit columns
                                    // Interpolate values from 0 to 1 between fMin and fMax
                                    // x_normalized = (x - min) / (max - min)
                                    if (afCorrValues[nCorrCounter] <= 0.0)
                                       afCorrValues[nCorrCounter] = 0.0; // Lowest normalized value. There is no correlation match
                                    // All other values are already normalized between 0 and 1

                                    //                           std::cout << nCorrCounter << ": " << afCorrValues[nCorrCounter] << " | ";

                                    // Paint pixel in gray-scale correlation map
                                    nValue = (int) (afCorrValues[nCorrCounter]
                                          * 255.0); // normalized correlation value for a grayscale
                                    m_corrMapImage->setPixel(x, y, nValue);
                                    nCorrCounter++;
                                 }
                              //                        std::cout << std::endl;
                           }
                  }
               break;
               //
               //            case PHASE_CORR: /* Fourier phase correlation */
               //               IP_crop(I2, 0, 0, nWI, nHI, II2); /* pad template      */
               //               IP_fft2D(II1, 1, Ifft1 = NEWIMAGE); /* pfTraversedTarget    FFT (F1) */
               //               IP_fft2D(II2, 1, Ifft2 = NEWIMAGE); /* template FFT (F2) */
               //               IP_complexConjugate(Ifft2, Ifft2); /* F2* is cmplx conj */
               //               IP_multiplyCmplx(Ifft1, Ifft2, Ifft1); /* F1 x F2*      */
               //
               //               /* divide F1 x F2* by the magnitude of (F1 x F2*) */
               //               total = nWI * nHI;
               //               pfImgTarget = (float *) Ifft1->buf[0];
               //               pfImgTemplate = (float *) Ifft1->buf[1];
               //               for (i = 0; i < total; i++)
               //                  {
               //                     mag = MAG(*pfImgTarget, *pfImgTemplate);
               //                     *pfImgTarget++ /= mag;
               //                     *pfImgTemplate++ /= mag;
               //                  }
               //
               //               /* find position of maximum in inverse FFT */
               //               IP_fft2D(Ifft1, -1, Ifft2);
               //               pfImgTarget = (float *) Ifft2->buf[0];
               //               pfImgTemplate = (float *) Ifft2->buf[1];
               //               for (y = 0; y < nHI; y++)
               //                  {
               //                     for (x = 0; x < nWI; x++)
               //                        {
               //                           mag = MAG(*pfImgTarget, *pfImgTemplate);
               //                           if (mag > fMax)
               //                              {
               //                                 fMax = mag;
               //                                 rnDx = x;
               //                                 rnDy = y;
               //                              }
               //                           pfImgTarget++;
               //                           pfImgTemplate++;
               //                        }
               //                  }
               //               IP_freeImage(Ifft1);
               //               IP_freeImage(Ifft2);
               //
               //               /* update position to avoid wrap-around; allow for -rnDx or -rnDy */
               //               if (rnDx > nWI / 2)
               //                  rnDx -= nWI;
               //               if (rnDy > nHI / 2)
               //                  rnDy -= nHI;
               //               fCorr = mag;
               //               break;

            default:
               QMessageBox::warning(this, tr("QCorr:"),
                     tr("Bad nMethod %1\n").arg(nMethod));
               return 0.;
            }
      }
   // CARLOS: needs review from up to this point on...^^^^^^^^^^^^^^^^^^

   //  free images
   // Deallocate arrays from memory
   delete[] afImgTarget;
   delete[] afImgTemplate;
   delete[] afCorrValues;

   return fCorr;
}

void
Qcorr::displayImage(QImage *image, QLabel *label)
{
   label->setPixmap(QPixmap::fromImage(*image));
   label->adjustSize();
}

void
Qcorr::displayImageLabel(QImage *image, ImgLabel *label)
{
   label->setPixmap(QPixmap::fromImage(*image));
   label->adjustSize();
   // m_labelLowerRightCornerPoint must be set here (in the parent) because the label size can change dynamically
   label->m_labelLowerRightCornerPoint
         = QPoint(label->width(), label->height());
}

float *
Qcorr::convertToGrayScaleFloat(const unsigned char * pchImgOriginalBits,
      int nSize, int nDepth)
{
   float * afImgGrayBits = new float[nSize];
   float grayValue = 0.0;
   int offsetBytes, pixNumber;

   switch (nDepth)
      {
      case 32: // ARGB image (alpha and color channels)
         offsetBytes = nDepth / 8;
         for (int i = 0; i < nSize; i++)
            {
               pixNumber = i * offsetBytes;
               grayValue = pchImgOriginalBits[pixNumber + 1] * 0.30; // Red value
               grayValue += pchImgOriginalBits[pixNumber + 2] * 0.59; // Green value
               grayValue += pchImgOriginalBits[pixNumber + 3] * 0.11; // Blue value
               afImgGrayBits[i] = grayValue;
            }
         break;
      case 24: // RGB image (3 color channels only)
         offsetBytes = nDepth / 8;
         for (int i = 0; i < nSize; i++)
            {
               pixNumber = i * offsetBytes;
               grayValue = pchImgOriginalBits[pixNumber] * 0.30; // Red value
               grayValue += pchImgOriginalBits[pixNumber + 1] * 0.59; // Green value
               grayValue += pchImgOriginalBits[pixNumber + 2] * 0.11; // Blue value
               afImgGrayBits[i] = grayValue;
            }
         break;
      default:
         // 1-bit monochrome and 8-bit grayscale images
         for (int i = 0; i < nSize; i++)
            {
               afImgGrayBits[i] = (float) pchImgOriginalBits[i];
            }
         break;
      }

   return afImgGrayBits;
}

void
Qcorr::updateStatusLabelWithDisparityInfo()
{
   m_nScanInterval = m_controlsWindow->getScanInterval();
   m_templateSize.setHeight(m_controlsWindow->getTemplateSize());
   m_templateSize.setWidth(m_controlsWindow->getTemplateSize());
   this->m_status_label->setText("Template Size: <b>" + QString::number(
         m_templateSize.width()) + "x" + QString::number(
         m_templateSize.height()) + "</b>px  |   Scan Interval: <b>"
         + QString::number(m_nScanInterval) + "</b>px");
}

// Temp:
bool
Qcorr::fileDumpQImage(const QString &fileName)
{
   QFile file(fileName);
   if (!file.open(QIODevice::WriteOnly))
      {
         QMessageBox::warning(this, tr("QCorr Image"), tr(
               "Cannot write file %1:\n%2.") .arg(file.fileName()) .arg(
               file.errorString()));
         return false;
      }
   QDataStream out(&file);
   out.setVersion(QDataStream::Qt_4_5);

   QApplication::setOverrideCursor(Qt::WaitCursor);

   // Helped to test that the bits dumped by QImage's bits() function
   // is the actual data (pixels) of the image without any header.
   // ...just pure pixel data!
   const unsigned char * imgTarget = m_rightImage->bits();

   int mysalt = 0; // just to see if the image has extra bytes that might be missing
   int imgBytes = m_rightImage->sizeInBytes() + mysalt;
//   int imgBytes = m_rightImage->numBytes() + mysalt;

   for (int byteN = 0; byteN < imgBytes; ++byteN)
      {
         out << quint8(imgTarget[byteN]);
      }
   QApplication::restoreOverrideCursor();
   return true;
}
