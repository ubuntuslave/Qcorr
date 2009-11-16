/*
 * targetImgLabel.cpp
 *
 *  Created on: Nov 15, 2009
 *      Author: carlos
 */

#include <QtGui>

#include "targetImgLabel.h"

//TargetImgLabel::TargetImgLabel(const QImage &labelImage, QWidget *parent) :
TargetImgLabel::TargetImgLabel(QWidget *parent) : QLabel(parent)
{
   m_bHasCorrResults = false;
   m_bHasImage = false;
}

TargetImgLabel::~TargetImgLabel()
{
   // TODO Auto-generated destructor stub
}

void TargetImgLabel::setImage(const QImage &labelImage)
{
   m_image = new QImage(labelImage);
   this->resize(m_image->size());
   m_bHasImage = true;

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

void TargetImgLabel::paintEvent(QPaintEvent * /* event */)
{
   if(m_bHasImage)
      {
      QPainter painter(this);
      painter.setCompositionMode(QPainter::CompositionMode_Xor);
      painter.drawImage(0, 0, *m_image);

       if(m_bHasCorrResults)
          {
          painter.setPen(QPen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap,
           Qt::RoundJoin));
          painter.setBrush( Qt::NoBrush);
           QRect rect(m_originPoint, m_rectSize);
          painter.drawRect(rect);
         }
      }
}

void TargetImgLabel::drawEnclosedMatch(const QPoint originPoint, const QSize rectSize)
{
   m_originPoint = originPoint;
   m_rectSize = rectSize;

   m_bHasCorrResults = true;

   update();
}

void TargetImgLabel::eraseEnclosedMatch()
{
   m_bHasCorrResults = false;
}


