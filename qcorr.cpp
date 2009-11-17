#include <QtGui>

#include "qcorr.h"
#include "globals.h"

Qcorr::Qcorr(QWidget *parent)
    : QMainWindow(parent)
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

}

void Qcorr::setImageLabels()
{
//   m_leftImage_label = new QLabel(scrollAreaWidgetContents);
//   m_leftImage_label = new QLabel;
   m_leftImage_label = new ImgLabel(this);
//   m_leftImage_label->setBackgroundRole(QPalette::Base);
   m_leftImage_label->setBackgroundRole(QPalette::Dark);
   m_leftImage_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
   m_leftImage_label->setScaledContents(true);
   m_leftImage_label->setMouseTracking(true);

   leftImage_scrollArea->setWidget(m_leftImage_label);
   leftImage_scrollArea->setBackgroundRole(QPalette::Dark);

   m_targetImage_label = new TargetImgLabel(this);  // Draw Right Image
//   rightImage_label->setBackgroundRole(QPalette::Base);
   m_targetImage_label->setBackgroundRole(QPalette::Dark);
   m_targetImage_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
   m_targetImage_label->setScaledContents(true);

   rightImage_scrollArea->setWidget(m_targetImage_label);
   rightImage_scrollArea->setBackgroundRole(QPalette::Dark);

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

   corr_pushButton->setEnabled(false); // This button should be initially disabled because there's no target image to correlate to

   // Create Correlation Method Dialog, which is initially hidden
   m_corrMethodDialog = new CorrMethod(this);

}

void Qcorr::createActions()
{
   connect(quit_pushButton, SIGNAL(clicked()), this, SLOT(close()));
   connect(leftBrowse_pushButton, SIGNAL(clicked()), this, SLOT(browseLeftImage()));
   connect(rightBrowse_pushButton, SIGNAL(clicked()), this, SLOT(browseRightImage()));
   connect(corr_pushButton, SIGNAL(clicked()), this, SLOT(correlate()));

   action_Quit->setShortcut(tr("Ctrl+Q"));
   connect(action_Quit, SIGNAL(triggered()), this, SLOT(close()));
}

// begin Q_SLOTS vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void Qcorr::browseLeftImage()
{
    QString initialName = leftImage_lineEdit->text();
    if (initialName.isEmpty())
        initialName = QDir::homePath();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose File"),
                                         initialName);
    fileName = QDir::toNativeSeparators(fileName);

    if (!fileName.isEmpty()) {

        leftImage_lineEdit->setText(fileName);
        m_leftImage = new QImage(fileName);

        if (m_leftImage->isNull()) {
            QMessageBox::information(this, tr("QCorr"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }

        this->displayImageLabel(m_leftImage, m_leftImage_label);   // Draw Left Image

        m_leftImage_label->setCursor(QCursor(Qt::CrossCursor));
        m_leftImage_label->setMouseTracking(true);
        m_leftImage_label->setFocusPolicy(Qt::ClickFocus);
    }
}

void Qcorr::browseRightImage()
{
    QString initialName = leftImage_lineEdit->text(); // Observes the Path of the Left Image most likely
    if (initialName.isEmpty())
        initialName = QDir::homePath();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose File"),
                                         initialName);
    fileName = QDir::toNativeSeparators(fileName);

    if (!fileName.isEmpty()) {


        rightImage_lineEdit->setText(fileName);
        m_rightImage = new QImage(fileName);

        if (m_rightImage->isNull()) {
            QMessageBox::information(this, tr("QCorr"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }

        m_targetImage_label->setImage(*m_rightImage);

        // CARLOS: just for testing:
        // To verify if the data has been converted to grayscale,
        // and that QImage's bits() function uses only the data pixels withou any formatting headers
//        convertToGrayScale(m_rightImage);
//
//        if(!fileDumpQImage(fileName + ".txt"))
//            return;

        update();

        corr_pushButton->setEnabled(true); // Now, this button can be enabled because a target image exists to correlate to
    }
}

void Qcorr::correlate()
{
   if(m_leftImage_label->m_rubberBand->isVisible())
      {
      m_templateImage = new QImage(m_leftImage->copy(m_leftImage_label->m_rubberBand->geometry()));

      m_templateSize = m_templateImage->size();

      m_corrMethodDialog->exec();   // Making sure that this dialog behaves modally
                                    // Otherwise, a dialog is not modal if it's invoked using show()

      if(m_corrMethodDialog->getMethod() == N0_CORR_METHOD)
         {
         m_targetImage_label->eraseEnclosedMatch();
         }
      else
         {
         // cast to a 1-channel grayscale image
         convertToGrayScale(m_rightImage);
         convertToGrayScale(m_templateImage);

         float fCorrLevel = findCorrelation( m_rightImage->bits(),
                                                  m_templateImage->bits(),
                                                  &m_nXoffset, &m_nYoffset,
                                                  m_corrMethodDialog->getMethod(),
                                                  false);
            // CARLOS: just for testing:
      //      this->displayImage(m_templateImage, rightImage_label);   // Draw Template on Right Label

            this->m_status_label->setText(
                                 "Finding Correlation for the <b>(" + QString::number(m_templateImage->width()) + "x"
                                 + QString::number(m_templateImage->height()) + ")px </b>Template ..." );

            this->corrResults_label->setText( "Method: " + QString::number(m_corrMethodDialog->getMethod()));

            // TO DO: Validate the results before allowing to draw the enclosing rectangle around the match
            if(fCorrLevel > 0)
               {
               m_matchingPoint = m_leftImage_label->m_rubberBand->pos();   // TEMP!!!!
               // CARLOS: it should eventually done this way:
//               m_matchingPoint.setX(m_nXoffset);
//               m_matchingPoint.setY(m_nYoffset);
               m_targetImage_label->drawEnclosedMatch(m_matchingPoint, m_templateSize);
               }
            else
               m_targetImage_label->eraseEnclosedMatch();
         }
      }
   else
      {
      this->m_status_label->setText("There is No template!");
      this->corrResults_label->clear();
      }
}

// end Q_SLOTS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

float Qcorr::findCorrelation(const unsigned char * imgTarget, const unsigned char * imgTemplate, int *dx, int *dy, int method, bool multires)
{
   int i, j, k, n, x, y, total;
   int x1, x2, y1, y2, mxlevel, lowres;
   float sum1, sum2, diff, corr;
   float avg, tmpl_pow, image_pow;
   float *p1, *p2, mag, *image, *ftemplate;
   float min, max;
   double xsz, ysz;


//   imageP II1, II2, Ifft1, Ifft2, Iblur, pyramid1[8], pyramid2[8];

   // temporarily here because dimensions are not passed directly
   /* image dimensions */
   int wI = m_rightImage->width();
   int hI = m_rightImage->height();
   int sizeI = wI*hI;

   /* template dimensions */
   int wT = m_templateImage->width();
   int hT = m_templateImage->height();
   int sizeT = wT*hT;

   /* error checking: size of image I1 must be >= than ftemplate I2 */
   if (!(wT <= wI && hT <= hI))
      {
      QMessageBox::warning(this, tr("QCorr"), tr("image is smaller than ftemplate\n"));
      return 0.;
      }

   // cast image into buffer of type float
   float fImgTarget[sizeI];
   for (int byteN = 0; byteN < sizeI; ++byteN) {
      fImgTarget[byteN] = (float) imgTarget[byteN];
   }

   // cast ftemplate into buffer of type float
   float fImgTemplate[sizeT];
   for (int byteN = 0; byteN < sizeT; ++byteN) {
      fImgTarget[byteN] = (float) imgTemplate[byteN];
   }


//   /*
//    * create image and ftemplate pyramids with original images at base;
//    * if no multiresolution is used, pyramids consist of only one level.
//    */
//   pyramid1[0] = II1; /* base: original image    */
//   pyramid2[0] = II2; /* base: original ftemplate */

// CARLOS: needs review from this point on... (and perhaps above, also) vvvvvvvvvvvvvv

   if (multires)
      {
         /* set lowest resolution for pyramid1 (empirically tested) */
         switch (method)
            {
            case CROSS_CORR:
            case SUM_SQ_DIFF:
               lowres = 64;
               break;
            case CORR_COEFF:
               lowres = 128;
               break;
//            case PHASE_CORR:
//               lowres = MAX(wI, hI); /* disable multires */
//               break;
            }

         /* update lowres if pyramid2 will become too small  */
         for (k = 1; (wI >> k) >= lowres && (hI >> k) >= lowres; k++)
            ;
         for (k--; (wT >> k) < 4 || (hT >> k) < 4; k--)
            lowres *= 2;

         /* compute lower-res versions for remaining pyramid levels */
         for (k = 1; (wI >> k) >= lowres && (hI >> k) >= lowres; k++)
            {
//               pyramid1[k] = NEWIMAGE;
//               pyramid2[k] = NEWIMAGE;
//// !!!!!!!!!!
//               // CARLOS: The resize must be done with a function (Perhaps, OpenCV)
//               IP_resize(pyramid1[k - 1], wI >> k, hI >> k, TRIANGLE, pyramid1[k]);
//               IP_resize(pyramid2[k - 1], wT >> k, hT >> k, TRIANGLE,
//                     pyramid2[k]);
            }
         mxlevel = k - 1;
      }
   else
      mxlevel = 0;

   /* init search window */
   x1 = 0;
   y1 = 0;
   x2 = (wI - wT) >> mxlevel;  // >> means: shift bit (divide by 2*mxlevel times)
   y2 = (hI - hT) >> mxlevel;

   /* multiresolution correlation: use results of lower-res correlation
    * (at the top of the pyramid) to narrow the search in the higher-res
    * correlation (towards the base of the pyramid).
    */
   for (n = mxlevel; n >= 0; n--)
      {
//         /* init vars based on pyramid at level n */
//         wI = pyramid1[n]->width;
//         hI = pyramid1[n]->height;
//         wT = pyramid2[n]->width;
//         hT = pyramid2[n]->height;

         /* pointers to image and ftemplate data */
//         p1 = (float *) pyramid1[n]->buf[0]; /* image    ptr */
//         p2 = (float *) pyramid2[n]->buf[0]; /* ftemplate ptr */
         *p1 = fImgTarget[0]; /* image    ptr */
         *p2 = fImgTemplate[0]; /* ftemplate ptr */

         /* init min and max */
         min = 10000000.;
         max = 0.;

         switch (method)
            {
            case CROSS_CORR: /* cross correlation */
               for (y = y1; y <= y2; y++)
                  { /* visit rows   */
                     for (x = x1; x <= x2; x++)
                        { /* slide window */
                           sum1 = sum2 = 0;
                           image = p1 + y * wI + x;
                           ftemplate = p2;
                           for (i = 0; i < hT; i++)
                              { /* convolution  */
                                 for (j = 0; j < wT; j++)
                                    {
                                       sum1 += (ftemplate[j] * image[j]);
                                       sum2 += (image[j] * image[j]);
                                    }
                                 image += wI;
                                 ftemplate += wT;
                              }
                           if (sum2 == 0)
                              continue;

                           corr = sum1 / sqrt(sum2);
                           if (corr > max)
                              {
                                 max = corr;
                                 *dx = x;
                                 *dy = y;
                              }
                        }
                  }

               /* update search window or normalize final correlation value */
//               if (n)
//                  { /* set search window for next pyramid level  */
//                     x1 = MAX(0, 2 * dx - n);
//                     y1 = MAX(0, 2 * dy - n);
//                     x2 = MIN(2 * wI, 2 * dx + n);
//                     y2 = MIN(2 * hI, 2 * dy + n);
//                  }
//               else
//                  { /* normalize correlation value at final level */
                     total = wT * hT;
                     for (i = tmpl_pow = 0; i < total; i++)
                        tmpl_pow += (p2[i] * p2[i]);
                     corr = max / sqrt(tmpl_pow);
//                  }
               break;

//            case SUM_SQ_DIFF: /* sum of squared differences */
//               for (y = y1; y <= y2; y++)
//                  { /* visit rows   */
//                     for (x = x1; x <= x2; x++)
//                        { /* slide window */
//                           sum1 = sum2 = 0;
//                           image = p1 + y * wI + x;
//                           ftemplate = p2;
//                           for (i = 0; i < hT; i++)
//                              { /* convolution  */
//                                 for (j = 0; j < wT; j++)
//                                    {
//                                       diff = ftemplate[j] - image[j];
//                                       sum1 += (diff * diff);
//                                       sum2 += (image[j] * image[j]);
//                                    }
//                                 image += wI;
//                                 ftemplate += wT;
//                              }
//                           if (sum2 == 0)
//                              continue;
//
//                           corr = sum1 / sqrt(sum2);
//                           if (corr < min)
//                              {
//                                 min = corr;
//                                 dx = x;
//                                 dy = y;
//                              }
//                        }
//                  }
//
//               /* update search window or normalize final correlation value */
//               if (n)
//                  { /* set search window for next pyramid level  */
//                     x1 = MAX(0, 2 * dx - n);
//                     y1 = MAX(0, 2 * dy - n);
//                     x2 = MIN(2 * wI, 2 * dx + n);
//                     y2 = MIN(2 * hI, 2 * dy + n);
//                  }
//               else
//                  { /* normalize correlation value at final level */
//                     total = wT * hT;
//                     for (i = tmpl_pow = 0; i < total; i++)
//                        tmpl_pow += (p2[i] * p2[i]);
//                     corr = min / sqrt(tmpl_pow);
//                  }
//               break;
//
//            case CORR_COEFF: /* correlation coefficient */
//               /* compute ftemplate average */
//               total = wT * hT;
//               for (i = avg = 0; i < total; i++)
//                  avg += p2[i];
//               avg /= total;
//
//               /* subtract average from template */
//               for (i = 0; i < total; i++)
//                  p2[i] -= avg;
//
//               /* compute template power */
//               for (i = tmpl_pow = 0; i < total; i++)
//                  tmpl_pow += (p2[i] * p2[i]);
//
//               /* compute local image average: blur with box filter */
//               xsz = wT + !(wT % 2); /* make filter width  odd */
//               ysz = hT + !(hT % 2); /* make filter height odd */
//               IP_blur(pyramid1[n], xsz, ysz, Iblur = NEWIMAGE);
//
//               /* subtract local image averages from pixels */
//               IP_subtractImage(pyramid1[n], Iblur, pyramid1[n]);
//               IP_freeImage(Iblur);
//
//               for (y = y1; y <= y2; y++)
//                  { /* visit rows   */
//                     for (x = x1; x <= x2; x++)
//                        { /* slide window */
//                           sum1 = sum2 = 0;
//                           image = p1 + y * wI + x;/* avgs  were  subtracted  */
//                           ftemplate = p2; /* from image and ftemplate */
//
//                           image_pow = 0;
//                           image = p1 + y * wI + x;
//                           for (i = 0; i < hT; i++)
//                              { /* convolution  */
//                                 for (j = 0; j < wT; j++)
//                                    {
//                                       sum1 += (ftemplate[j] * image[j]);
//                                       image_pow += (image[j] * image[j]);
//                                    }
//                                 image += wI;
//                                 ftemplate += wT;
//                              }
//
//                           sum2 = image_pow * tmpl_pow;
//                           corr = sum1 / sqrt(sum2);
//                           if (corr > max)
//                              {
//                                 max = corr;
//                                 dx = x;
//                                 dy = y;
//                              }
//                        }
//                  }
//
//               /* update search window or set final correlation value */
//               if (n)
//                  { /* set search window for next pyramid level */
//                     x1 = MAX(0, 2 * dx - n);
//                     y1 = MAX(0, 2 * dy - n);
//                     x2 = MIN(2 * wI, 2 * dx + n);
//                     y2 = MIN(2 * hI, 2 * dy + n);
//                  }
//               else
//                  { /* set correlation value at final level */
//                     corr = max;
//                  }
//               break;
//
//            case PHASE_CORR: /* Fourier phase correlation */
//               IP_crop(I2, 0, 0, wI, hI, II2); /* pad template      */
//               IP_fft2D(II1, 1, Ifft1 = NEWIMAGE); /* image    FFT (F1) */
//               IP_fft2D(II2, 1, Ifft2 = NEWIMAGE); /* template FFT (F2) */
//               IP_complexConjugate(Ifft2, Ifft2); /* F2* is cmplx conj */
//               IP_multiplyCmplx(Ifft1, Ifft2, Ifft1); /* F1 x F2*      */
//
//               /* divide F1 x F2* by the magnitude of (F1 x F2*) */
//               total = wI * hI;
//               p1 = (float *) Ifft1->buf[0];
//               p2 = (float *) Ifft1->buf[1];
//               for (i = 0; i < total; i++)
//                  {
//                     mag = MAG(*p1, *p2);
//                     *p1++ /= mag;
//                     *p2++ /= mag;
//                  }
//
//               /* find position of maximum in inverse FFT */
//               IP_fft2D(Ifft1, -1, Ifft2);
//               p1 = (float *) Ifft2->buf[0];
//               p2 = (float *) Ifft2->buf[1];
//               for (y = 0; y < hI; y++)
//                  {
//                     for (x = 0; x < wI; x++)
//                        {
//                           mag = MAG(*p1, *p2);
//                           if (mag > max)
//                              {
//                                 max = mag;
//                                 dx = x;
//                                 dy = y;
//                              }
//                           p1++;
//                           p2++;
//                        }
//                  }
//               IP_freeImage(Ifft1);
//               IP_freeImage(Ifft2);
//
//               /* update position to avoid wrap-around; allow for -dx or -dy */
//               if (dx > wI / 2)
//                  dx -= wI;
//               if (dy > hI / 2)
//                  dy -= hI;
//               corr = mag;
//               break;

            default:
               QMessageBox::warning(this, tr("QCorr:"), tr("Bad method %1\n").arg(method));
               return 0.;
            }
      }
   // CARLOS: needs review from up to this point on...^^^^^^^^^^^^^^^^^^

//   /* free images */
//   if (I1 != II1)
//      IP_freeImage(II1);
//   if (I2 != II2)
//      IP_freeImage(II2);
//   for (n = 1; n <= mxlevel; n++)
//      {
//         IP_freeImage(pyramid1[n]);
//         IP_freeImage(pyramid2[n]);
//      }

//   *xx = dx;
//   *yy = dy;
   return corr;
}

void Qcorr::displayImage(QImage *image, QLabel *label)
{
   label->setPixmap(QPixmap::fromImage(*image));
   label->adjustSize();
}

void Qcorr::displayImageLabel(QImage *image, ImgLabel *label)
{
   label->setPixmap(QPixmap::fromImage(*image));
   label->adjustSize();
}

void Qcorr::convertToGrayScale(QImage *image)
{
   QVector<QRgb> colorTab(256);  // for an 8-bit scale color table

   for(int i=0; i<= 255; i++)
      {
         colorTab[i] = qRgb(i,i,i); // For a gray-scale color table
      }

   *image = image->convertToFormat(QImage::Format_Indexed8, colorTab, Qt::ThresholdDither );

   this->m_status_label->setText(
                                    "GRAY SCALE image has: <b>(" + QString::number(image->numBytes()) +
                                    "</b> bytes and <b> " + QString::number(image->numColors()) + "</b> colors"
                                    );
}

// Temp:
bool Qcorr::fileDumpQImage(const QString &fileName)
{
   QFile file(fileName);
       if (!file.open(QIODevice::WriteOnly)) {
           QMessageBox::warning(this, tr("QCorr Image"),
                                tr("Cannot write file %1:\n%2.")
                                .arg(file.fileName())
                                .arg(file.errorString()));
           return false;
       }
       QDataStream out(&file);
       out.setVersion(QDataStream::Qt_4_5);

       QApplication::setOverrideCursor(Qt::WaitCursor);

       // Helped to test for sure that the bits dumped by QImage's bits() function
       // is the actual data (pixels) of the image without any header.
       // ...just pure pixel data!
       const unsigned char * imgTarget = m_rightImage->bits();

       int mysalt = 0;  // just to see if the image has extra bytes that might be missing
       int imgBytes = m_rightImage->numBytes() + mysalt;

       for (int byteN = 0; byteN < imgBytes; ++byteN) {
          out << quint8(imgTarget[byteN]);
       }
       QApplication::restoreOverrideCursor();
       return true;
}
