/*
 * imgLabel.cpp
 *
 *  Created on: Nov 11, 2009
 *      Author: carlos
 */

#include <QtGui>

#include "imgLabel.h"
#include "qcorr.h"

ImgLabel::ImgLabel(Qcorr *parentWindow, QWidget *parent) :
   QLabel(parent)
{
   m_imgLabel = new QLabel;
   m_parentWindow = parentWindow; // Point to the Qcorr MainWindow

   m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
   m_rubberBand->setCursor(Qt::SizeAllCursor);
   m_rubberBand->setMouseTracking(true);

   m_bStartedTemplateSelection = false;
   m_bMouseIsPressed = false;
}

ImgLabel::~ImgLabel()
{
   // TODO Auto-generated destructor stub
}

void
ImgLabel::mousePressEvent(QMouseEvent *event)
{
   m_bMouseIsPressed = true;

   m_originPoint = event->pos();

   if (m_rubberBand->isHidden() && (m_bStartedTemplateSelection == false))
      {
         m_rubberBand->setGeometry(QRect(m_originPoint, QSize()));
      }
   else
      {
         m_rubberBand->hide();
         m_bStartedTemplateSelection = false;
      }

   update();
}

void
ImgLabel::mouseMoveEvent(QMouseEvent *event)
{
   if (m_bMouseIsPressed)
      {
         m_rubberBand->show();

         m_bStartedTemplateSelection = true;

         m_finalPoint = event->pos();

         m_rubberBand->setGeometry(
               QRect(m_originPoint, m_finalPoint).normalized());

         m_parentWindow->m_status_label->setText("[X0:" + QString::number(
               m_originPoint.x()) + "px, " + "Y0:" + QString::number(
               m_originPoint.y()) + "px]" + "<b> to </b>" + "[X1:"
               + QString::number(m_finalPoint.x()) + "px, " + "Y1: "
               + QString::number(m_finalPoint.y()) + "px]");
      }
   else if (m_rubberBand->isHidden())
      {
         m_bStartedTemplateSelection = false;
         m_originPoint = event->pos(); // Use mouse move position only
         m_parentWindow->m_status_label->setText("[X:" + QString::number(
               m_originPoint.x()) + "px, " + "Y:" + QString::number(
               m_originPoint.y()) + "px]");
      }
}

void
ImgLabel::mouseReleaseEvent(QMouseEvent *event)
{
   m_bMouseIsPressed = false;

   if (m_rubberBand->isVisible())
      {
//         this->setCursor(Qt::SizeAllCursor);

         //      m_bStartedTemplateSelection = false;

         // determine selection, for example using QRect::intersects()
         // and QRect::contains().

      }
}
