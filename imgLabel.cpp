/*
 * imgLabel.cpp
 *
 *  Created on: Nov 11, 2009
 *      Author: carlos
 */

#include <QtGui>

#include "imgLabel.h"
#include "qcorr.h"

ImgLabel::ImgLabel(Qcorr *parentWindow, QWidget *parent) : QLabel(parent)
{
   m_imgLabel = new QLabel;
   m_parentWindow = parentWindow;   // Point to the Qcorr MainWindow

   m_pixelPoint = new QPoint;
}

ImgLabel::~ImgLabel()
{
   // TODO Auto-generated destructor stub
}

void ImgLabel::mousePressEvent(QMouseEvent *event)
{
      m_xpos = event->x();
      m_ypos = event->y();

      m_parentWindow->m_status_label->setText(  "X: " + QString::number(m_xpos) + "px" +
                                                " Y: " + QString::number(m_ypos) + "px");
      update();
}
