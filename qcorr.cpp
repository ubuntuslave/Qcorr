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
   return 1.0;   //temp
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

