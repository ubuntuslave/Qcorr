#include "controlswindow.h"
#include "qcorr.h"

ControlsWindow::ControlsWindow(Qcorr *parentWindow, QWidget *parent) :
   QDialog(parent)
{
   ui.setupUi(this);

   m_parentWindow = parentWindow; // Point to the Qcorr MainWindow

   this->setMinimumSize(ui.controlsWindow_frame->size());

   setEnableSpinBoxes(false);

   createActions();

   // Default values:
   m_nScanInterval = 10;
   m_nTemplateSize = 32;

}

ControlsWindow::~ControlsWindow()
{
   emit this->close();
   delete this; // Destroys itself
}

void
ControlsWindow::createActions()
{
   connect(ui.close_pushButton, SIGNAL(clicked()), this, SLOT(close()));

   connect(ui.scanInterval_spinBox, SIGNAL(valueChanged(int)), this,
         SLOT(setScanInterval(int)));

   connect(ui.templateSize_spinBox, SIGNAL(valueChanged(int)), this,
         SLOT(setTemplateSize(int)));

}

void
ControlsWindow::setEnableSpinBoxes(bool bEnable)
{
   // Setup default values for spinBoxes

   ui.scanInterval_spinBox->setEnabled(bEnable);
   ui.templateSize_spinBox->setEnabled(bEnable);

   if (bEnable)
      {
         // Sets maximum value of scanInterval_spinBox according to the right image's width
         ui.scanInterval_spinBox->setMaximum(
               m_parentWindow->m_rightImage->width());
         // Sets maximum value of templateSize_spinBox according to the right image's width
         ui.templateSize_spinBox->setMaximum(
               m_parentWindow->m_rightImage->width());
      }
}

// begin Q_SLOTS vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void
ControlsWindow::setScanInterval(int nValue)
{
   m_nScanInterval = nValue;

   updateParentStatusLabel();
}

void
ControlsWindow::setTemplateSize(int nValue)
{
   m_nTemplateSize = nValue;
   updateParentStatusLabel();

}
// end Q_SLOTS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void
ControlsWindow::updateParentStatusLabel()
{
   m_parentWindow->m_status_label->setText("Template Size: <b>"
         + QString::number(m_nTemplateSize) + "x" + QString::number(
         m_nTemplateSize) + "</b>px  |   Scan Interval: <b>" + QString::number(
         m_nScanInterval) + "</b>px");
}
