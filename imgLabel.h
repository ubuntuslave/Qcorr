/*
 * imgLabel.h
 *
 *  Created on: Nov 11, 2009
 *      Author: carlos
 *
 *  Description: Subclassing QLabel in order to allow higher control of mouse-event positions and other properties.
 */

#ifndef IMGLABEL_H_
#define IMGLABEL_H_

#include <QtGui/QLabel>
class QMainWindow;
class QRubberBand;
class QPoint;

class Qcorr;   // using this friend class

class ImgLabel : public QLabel
{
   Q_OBJECT

   public:
      ImgLabel(Qcorr *parentWindow, QWidget *parent = 0);

      virtual
      ~ImgLabel();


   private:
      QLabel *m_imgLabel;
      Qcorr *m_parentWindow;  // Pointer to Main Window Object (There should be only one on these)

      QRubberBand *m_rubberBand;
      QPoint m_originPoint;
      QPoint m_finalPoint;
      bool m_bStartedTemplateSelection;
      bool m_bMouseIsPressed;

   protected:
       void mousePressEvent(QMouseEvent *event);
       void mouseMoveEvent(QMouseEvent *event);
       void mouseReleaseEvent(QMouseEvent *event);
};

#endif /* IMGLABEL_H_ */
