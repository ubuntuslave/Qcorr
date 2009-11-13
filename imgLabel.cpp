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

   setTemplateFlags(false);

//   this->stackUnder(m_rubberBand);  //Places the widget under the rubberBand in the parent widget's stack.
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

         QPoint newOriginPoint = QPoint(0,0);

         if(m_bMouseInTemplateRegion)
            {
            newOriginPoint = m_originPoint - (m_finalPoint - event->pos());
//            m_rubberBand->move(m_originPoint - (m_finalPoint - event->pos()));
            m_rubberBand->move(newOriginPoint);
            m_parentWindow->m_status_label->setText("[X:" + QString::number(
                  newOriginPoint.x()) + "px, " + "Y:" + QString::number(
                        newOriginPoint.y()) + "px]");
            }
         else
            {
            m_finalPoint = event->pos();
            m_rubberBand->setGeometry(
                           QRect(m_originPoint, m_finalPoint).normalized());
            setTemplateFlags(false);

            m_parentWindow->m_status_label->setText(
                           "[X0:" + QString::number(m_originPoint.x()) + "px, " + "Y0:" + QString::number(
                           m_originPoint.y()) + "px]" + "<b> to </b>" + "[X1:"
                           + QString::number(m_finalPoint.x()) + "px, " + "Y1:"
                           + QString::number(m_finalPoint.y()) + "px]");
            }

      }
   else if(m_rubberBand->isVisible())
      {
      int mouseX = event->pos().x();
      int mouseY = event->pos().y();

      // Hackish way of changing the mouse cursor when inside the QRubberBand region:
      if(((mouseX > m_originPoint.x()) && (mouseY > m_originPoint.y())
            && (mouseX < m_finalPoint.x()) && (mouseY < m_finalPoint.y()) )
            || // When the region was selected from bottom to top
            ((mouseX < m_originPoint.x()) && (mouseY < m_originPoint.y())
            && (mouseX > m_finalPoint.x()) && (mouseY > m_finalPoint.y()) )
           )
         {
         this->setCursor(Qt::SizeAllCursor);
         m_bMouseInTemplateRegion = true;
         }
      // Change the cursor at the edges:
      else if((mouseX == m_originPoint.x()) || (mouseX == m_finalPoint.x()) )
         {
         this->setCursor(Qt::SizeHorCursor);
         // TODO: Implement resize on the horizontal sides
         }
      else if((mouseY == m_originPoint.y()) || (mouseY == m_finalPoint.y()) )
         {
         this->setCursor(Qt::SizeVerCursor);
         // TODO: Implement resize on the horizontal sides
         }
      else
         this->setCursor(Qt::CrossCursor);
      }
   else if (m_rubberBand->isHidden())
      {
         m_bStartedTemplateSelection = false;
         m_originPoint = event->pos();
         // Show mouse moving position only
         m_parentWindow->m_status_label->setText("[X:" + QString::number(
               m_originPoint.x()) + "px, " + "Y:" + QString::number(
               m_originPoint.y()) + "px]");
         setTemplateFlags(false);
      }
}

void
ImgLabel::mouseReleaseEvent(QMouseEvent *event)
{
   m_bMouseIsPressed = false;

   if (m_rubberBand->isVisible())
      {
      // Obtain actual origin and final Points
      m_originPoint = m_rubberBand->pos(); // Set new position of the Points
      m_finalPoint.setX(m_originPoint.x() + m_rubberBand->width());
      m_finalPoint.setY(m_originPoint.y() + m_rubberBand->height());

      // ------------------------------------------------------------
      //To process the rectangular regions, use something like:
//      QImage::copy ( const QRect & rectangle = QRect() ) const
      // for further processing
      // It's missing QImage member function that was set as QPixmap on the MainWindow app (qcorr.cpp)
      //----------------------------------------------------------

         // determine selection, for example using QRect::intersects()
         // and QRect::contains().

      }
}

void ImgLabel::setTemplateFlags(bool status)
{
   m_bMouseInTemplateRegion = status;
   m_bMouseAtTemplateTopEdge = status;
   m_bMouseAtTemplateBottomEdge = status;
   m_bMouseAtTemplateLeftEdge = status;
   m_bMouseAtTemplateRightEdge = status;
}
