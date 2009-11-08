#include <QtGui>

#include "qcorr.h"

Qcorr::Qcorr(QWidget *parent)
    : QMainWindow(parent)
{
	setupUi(this);

	setImageLabels();

   createActions();

   this->setWindowTitle(tr("QCorr"));
   this->setCentralWidget(main_frame);
//   resize(500, 400);
}

Qcorr::~Qcorr()
{

}

void Qcorr::setImageLabels()
{
//   leftImage_label = new QLabel(scrollAreaWidgetContents);
   leftImage_label = new QLabel;
//   leftImage_label->setBackgroundRole(QPalette::Base);
   leftImage_label->setBackgroundRole(QPalette::Dark);
   leftImage_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
   leftImage_label->setScaledContents(true);

   leftImage_scrollArea->setWidget(leftImage_label);
   leftImage_scrollArea->setBackgroundRole(QPalette::Dark);

   rightImage_label = new QLabel;
//   rightImage_label->setBackgroundRole(QPalette::Base);
   rightImage_label->setBackgroundRole(QPalette::Dark);
   rightImage_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
   rightImage_label->setScaledContents(true);

   rightImage_scrollArea->setWidget(rightImage_label);
   rightImage_scrollArea->setBackgroundRole(QPalette::Dark);

}

void Qcorr::createActions()
{
   connect(quit_pushButton, SIGNAL(clicked()), this, SLOT(close()));
   connect(leftBrowse_pushButton, SIGNAL(clicked()), this, SLOT(browseLeftImage()));
   connect(rightBrowse_pushButton, SIGNAL(clicked()), this, SLOT(browseRightImage()));

   action_Quit->setShortcut(tr("Ctrl+Q"));
   connect(action_Quit, SIGNAL(triggered()), this, SLOT(close()));
}

//void Qcorr::adjustScrollBar(QScrollBar *scrollBar, double factor)
//{
//    scrollBar->setValue(int(factor * scrollBar->value()
//                            + ((factor - 1) * scrollBar->pageStep()/2)));
//}

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

        this->displayImage(m_leftImage, leftImage_label);   // Draw Left Image

        leftImage_label->setCursor(QCursor(Qt::CrossCursor));
        leftImage_label->setMouseTracking(true);
        leftImage_label->setFocusPolicy(Qt::ClickFocus);
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

        this->displayImage(m_rightImage, rightImage_label);   // Draw Right Image
    }
}

void Qcorr::displayImage(QImage *image, QLabel *label)
{
   label->setPixmap(QPixmap::fromImage(*image));
   label->adjustSize();
}
