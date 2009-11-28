/*
 * targetImgLabel.h
 *
 *  Created on: Nov 15, 2009
 *      Author: carlos
 *
 *  Description: Subclassing QLabel in order to allow higher control of painting the results above the label.
 */

#ifndef TARGETIMGLABEL_H_
#define TARGETIMGLABEL_H_

#include <QtGui/QLabel>
class QPoint;
class QImage;

class TargetImgLabel : public QLabel
{
   Q_OBJECT

   public:
      TargetImgLabel(QWidget *parent = 0);
      virtual
      ~TargetImgLabel();
      void setImage(const QImage &labelImage);
      void overlayImage(const QImage &otherImage);
      void drawEnclosedMatch(const QPoint originPoint, const QSize rectSize);
      void eraseEnclosedMatch();

   private:
      QImage *m_image;
      QImage *m_overlayImage;
      QPoint m_originPoint;
      QSize m_rectSize;

      bool m_bHasCorrResults;
      bool m_bHasImage;
      bool m_bHasOverlayImage;

   protected:
//       void mousePressEvent(QMouseEvent *event);
//       void mouseMoveEvent(QMouseEvent *event);
//       void mouseReleaseEvent(QMouseEvent *event);
       void paintEvent(QPaintEvent * /* event */);

};

#endif /* TARGETIMGLABEL_H_ */
