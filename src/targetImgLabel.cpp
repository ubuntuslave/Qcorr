/*
 * targetImgLabel.cpp
 *
 *  Created on: Nov 15, 2009
 *      Author: carlos
 */

#include <QtGui>

#include "targetImgLabel.h"

TargetImgLabel::TargetImgLabel(QWidget *parent) :
   QLabel(parent)
{
   m_bHasCorrResults = false;
   m_bHasImage = false;
   m_bHasOverlayImage = false;
}

TargetImgLabel::~TargetImgLabel()
{
   // TODO Auto-generated destructor stub
}

void
TargetImgLabel::setImage(const QImage &labelImage)
{
   m_image = new QImage(labelImage);

   this->resize(m_image->size());
   m_bHasImage = true;
   m_bHasOverlayImage = false;

   update();
}
void
TargetImgLabel::overlayImage(const QImage &otherImage, int nXoffset,
      int nYoffset)
{
   m_overlayImage = new QImage(otherImage);
   m_nXoffset = nXoffset;
   m_nYoffset = nYoffset;
   m_bHasOverlayImage = true;
   update();
}
// CARLOS: just for testing
//void TargetImgLabel::mousePressEvent(QMouseEvent *event)
//{
//   m_bHasCorrResults = true;
//
//   m_originPoint = event->pos();
//
//   update();
//
//}

void
TargetImgLabel::paintEvent(QPaintEvent * /* event */)
{
   if (m_bHasImage)
      {
         QImage imageWithOverlay = QImage(m_image->size(),
               QImage::Format_ARGB32_Premultiplied);
         QPainter painter(&imageWithOverlay);

         painter.setCompositionMode(QPainter::CompositionMode_Source);
         painter.fillRect(imageWithOverlay.rect(), Qt::transparent);

         painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
         painter.drawImage(0, 0, *m_image);

         if (m_bHasOverlayImage)
            {
               painter.setCompositionMode(QPainter::CompositionMode_Screen);
               painter.drawImage(m_nXoffset, m_nYoffset, *m_overlayImage);
            }

         if (m_bHasCorrResults)
            {
               painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

               painter.setPen(QPen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap,
                     Qt::RoundJoin));
               painter.setBrush(Qt::NoBrush);
               QRect rect(m_originPoint, m_rectSize);
               painter.drawRect(rect);
            }

         painter.end();

         QPainter painter2(this);
         painter2.drawImage(0, 0, imageWithOverlay);
         painter2.end();

      }
}

void
TargetImgLabel::drawEnclosedMatch(const QPoint originPoint,
      const QSize rectSize)
{
   m_originPoint = originPoint;
   m_rectSize = rectSize;

   m_bHasCorrResults = true;

   update();
}

void
TargetImgLabel::eraseEnclosedMatch()
{
   m_bHasCorrResults = false;
   m_bHasOverlayImage = false;
}

