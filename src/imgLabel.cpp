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
   m_parentWindow = parentWindow; // Point to the Qcorr MainWindow

   m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
//   m_rubberBand->setCursor(Qt::CrossCursor);
   this->setSelectable(false);

   m_rubberBand->setMouseTracking(true);

   setSelectable(false);

   m_bStartedTemplateSelection = false;
   m_bMouseIsPressed = false;

   setTemplateFlags(false);

   m_labelUpperLeftCornerPoint = QPoint(0,0);
   // m_labelLowerRightCornerPoint must be RESET from the parent (since the label size can dynamically change)
//   m_labelUpperLeftCornerPoint = QPoint(this->width(), this->height());

}

ImgLabel::~ImgLabel()
{
   // TODO Auto-generated destructor stub
}

void ImgLabel::setSelectable(bool bHasRubberBand)
{
   // TODO: needs reviewing (it's just a place holder for now)
   m_bHasRubberBand = bHasRubberBand;
   if(m_bHasRubberBand)
      this->setCursor(Qt::CrossCursor);
   else
      {
      this->setCursor(Qt::ArrowCursor);
      m_rubberBand->hide();
      }

}

void
ImgLabel::mousePressEvent(QMouseEvent *event)
{
   m_bMouseIsPressed = true;

   m_currentPressedPoint = event->pos();
   m_mousePosPoint1.setX(-1); // Reset the flag used to know when the mouse is being dragged around


   if (m_rubberBand->isHidden() && (m_bStartedTemplateSelection == false))
      {
         m_originPoint = event->pos();
         m_rubberBand->setGeometry(QRect(m_originPoint, QSize()));
      }
   else
      {
      if(m_bHasRubberBand)
         this->setCursor(Qt::CrossCursor);
      else
         {
         this->setCursor(Qt::ArrowCursor);
         }
//         this->setCursor(Qt::CrossCursor);
      m_rubberBand->hide();
      }

   update();
}

void
ImgLabel::mouseMoveEvent(QMouseEvent *event)
{
   if (m_bMouseIsPressed && m_bHasRubberBand)
      {
         m_rubberBand->show();

         m_bStartedTemplateSelection = true;

         QPoint newOriginPoint = QPoint(0,0);

         if(m_bMouseInTemplateRegion)
            {

            if(m_mousePosPoint1.x() < 0)
               {
                  m_mousePosPoint1 = event->pos(); // Sets to the position of the mouse position when it's dragged for the first time
               }
            else
               {
               m_mousePosPoint2 = event->pos();

               QPoint offsetPoint = m_mousePosPoint1 - m_mousePosPoint2;

               newOriginPoint = m_originPoint - offsetPoint; //m_currentPressedPoint - (m_finalPoint - event->pos());

               QPoint movedFinalPoint;

               movedFinalPoint.setX(newOriginPoint.x() + m_rubberBand->width());
               movedFinalPoint.setY(newOriginPoint.y() + m_rubberBand->height());

               // Validate new template's position to be within the label's margins
               if((newOriginPoint.x() >= m_labelUpperLeftCornerPoint.x())
                     && (movedFinalPoint.x() <= m_labelLowerRightCornerPoint.x())
                     )
                  {
                     m_nXNewPos = newOriginPoint.x();
                  }
               if((newOriginPoint.y() >= m_labelUpperLeftCornerPoint.y())
                     && (movedFinalPoint.y() <= m_labelLowerRightCornerPoint.y())
                     )
                  {
                     m_nYNewPos = newOriginPoint.y();
                  }

                  newOriginPoint.setX(m_nXNewPos);
                  newOriginPoint.setY(m_nYNewPos);
                  m_rubberBand->move(newOriginPoint);
                  displayCoordinatesOnStatusLabel(newOriginPoint, movedFinalPoint);

               }
            }
         else if(m_bMouseAtTemplateTopEdge)
            {
            newOriginPoint = QPoint(m_originPoint.x(), event->pos().y());

            // Validate new template's size to be within the label's margins
            if((newOriginPoint.y() >= m_labelUpperLeftCornerPoint.y())
                   && (newOriginPoint.y() <= m_labelLowerRightCornerPoint.y())
                   )
               {
               m_rubberBand->setGeometry(QRect(newOriginPoint, m_finalPoint).normalized());
               displayCoordinatesOnStatusLabel(newOriginPoint, m_finalPoint);
               }
            }
         else if(m_bMouseAtTemplateBottomEdge)
            {
            newOriginPoint = QPoint(m_finalPoint.x(), event->pos().y());

            // Validate new template's size to be within the label's margins
            if((newOriginPoint.y() >= m_labelUpperLeftCornerPoint.y())
                   && (newOriginPoint.y() <= m_labelLowerRightCornerPoint.y())
                   )
               {
               m_rubberBand->setGeometry(QRect(m_originPoint, newOriginPoint).normalized());
               displayCoordinatesOnStatusLabel(m_originPoint, newOriginPoint);
               }
            }
         else if(m_bMouseAtTemplateLeftEdge)
            {
            newOriginPoint = QPoint(event->pos().x(), m_originPoint.y());

            // Validate new template's size to be within the label's margins
            if((newOriginPoint.x() >= m_labelUpperLeftCornerPoint.x())
                  && (newOriginPoint.x() <= m_labelLowerRightCornerPoint.x())
                  )
               {
               m_rubberBand->setGeometry(QRect(newOriginPoint, m_finalPoint).normalized());
               displayCoordinatesOnStatusLabel(newOriginPoint, m_finalPoint);
               }
            }
         else if(m_bMouseAtTemplateRightEdge)
            {
            newOriginPoint = QPoint(event->pos().x(), m_finalPoint.y());

            // Validate new template's size to be within the label's margins
            if((newOriginPoint.x() >= m_labelUpperLeftCornerPoint.x())
                  && (newOriginPoint.x() <= m_labelLowerRightCornerPoint.x())
                  )
               {
               m_rubberBand->setGeometry(QRect(m_originPoint, newOriginPoint).normalized());
               displayCoordinatesOnStatusLabel(m_originPoint, newOriginPoint);
               }
            }
         else
            { // Making a selection with the rubber band
            // Validate rubber-band selection to be within the label's margins
              if((event->pos().x() >= m_labelUpperLeftCornerPoint.x())
                    && (event->pos().x() <= m_labelLowerRightCornerPoint.x())
                    )
                 {
                    m_nXNewPos = event->pos().x();
                 }
              if((event->pos().y() >= m_labelUpperLeftCornerPoint.y())
                    && (event->pos().y() <= m_labelLowerRightCornerPoint.y())
                    )
                 {
                    m_nYNewPos = event->pos().y();
                 }

   //            m_finalPoint = event->pos();
               m_finalPoint.setX(m_nXNewPos);
               m_finalPoint.setY(m_nYNewPos);


               m_rubberBand->setGeometry(
                              QRect(m_currentPressedPoint, m_finalPoint).normalized());
               setTemplateFlags(false);
               displayCoordinatesOnStatusLabel(m_currentPressedPoint, m_finalPoint);
               }
      }
   else
      {
         if(m_rubberBand->isVisible())
         {
         checkTemplateRegions(event->pos().x(), event->pos().y());
         }
         else
         {
            m_bStartedTemplateSelection = false;
            m_currentPressedPoint = event->pos();
            displayCoordinatesOnStatusLabel(m_currentPressedPoint, m_currentPressedPoint); // Show mouse moving position only
            setTemplateFlags(false);
         }
      }
}

void
ImgLabel::mouseReleaseEvent(QMouseEvent *event)
{
   m_bMouseIsPressed = false;
   m_bStartedTemplateSelection = false;

   if (m_rubberBand->isVisible())
      {
      // Obtain actual origin and final Points
      m_originPoint = m_rubberBand->pos(); // Set new position of the Points
      m_finalPoint.setX(m_originPoint.x() + m_rubberBand->width());
      m_finalPoint.setY(m_originPoint.y() + m_rubberBand->height());

      checkTemplateRegions(event->pos().x(), event->pos().y());
      }
}

void ImgLabel::setTemplateFlags(bool bStatus)
{
   m_bMouseInTemplateRegion = bStatus;
   m_bMouseAtTemplateTopEdge = bStatus;
   m_bMouseAtTemplateBottomEdge = bStatus;
   m_bMouseAtTemplateLeftEdge = bStatus;
   m_bMouseAtTemplateRightEdge = bStatus;
}

void ImgLabel::checkTemplateRegions(int mouseX, int mouseY)
{
   m_bMouseAtTemplateTopEdge = (mouseY == m_originPoint.y());
   m_bMouseAtTemplateBottomEdge = (mouseY == m_finalPoint.y());
   m_bMouseAtTemplateLeftEdge = (mouseX == m_originPoint.x());
   m_bMouseAtTemplateRightEdge = (mouseX == m_finalPoint.x());

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
   else if(m_bMouseAtTemplateLeftEdge || m_bMouseAtTemplateRightEdge )
      {
      this->setCursor(Qt::SizeHorCursor);
      m_bMouseInTemplateRegion = false;
      }
   else if(m_bMouseAtTemplateTopEdge || m_bMouseAtTemplateBottomEdge )
      {
      this->setCursor(Qt::SizeVerCursor);
      m_bMouseInTemplateRegion = false;
      }
   else
      {
      this->setCursor(Qt::CrossCursor);
      setTemplateFlags(false);
      }
}

void ImgLabel::displayCoordinatesOnStatusLabel(QPoint &point0, QPoint &point1)
{
   m_parentWindow->m_status_label->setText(
                  "Template: (" + QString::number(point0.x()) + ", " +
                  QString::number(point0.y()) + ")px " + "<b> to </b>" +
                  " (" + QString::number(point1.x()) + ", " + QString::number(point1.y()) + ")px");
}
