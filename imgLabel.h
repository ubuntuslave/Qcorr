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
      friend class Qcorr; // Make the Qcorr class a friend of this ImgLabel class
                         // Thus, all members from ImgLabel are accessible by a Qcorr object

      Qcorr *m_parentWindow;  // Pointer to Main Window Object (There should be only one on these)

      QRubberBand *m_rubberBand;
      QPoint m_originPoint;
      QPoint m_finalPoint;
      QPoint m_currentPressedPoint;
      QPoint m_labelUpperLeftCornerPoint, m_labelLowerRightCornerPoint;
      QPoint m_mousePosPoint1, m_mousePosPoint2;

      bool m_bMouseIsPressed;
      bool m_bStartedTemplateSelection;
      bool m_bMouseInTemplateRegion;
      bool m_bMouseAtTemplateTopEdge;
      bool m_bMouseAtTemplateBottomEdge;
      bool m_bMouseAtTemplateLeftEdge;
      bool m_bMouseAtTemplateRightEdge;

      void setTemplateFlags(bool status);
      void checkTemplateRegions(int mouseX, int mouseY);
      void displayCoordinatesOnStatusLabel(QPoint &point0, QPoint &point1);
   protected:
       void mousePressEvent(QMouseEvent *event);
       void mouseMoveEvent(QMouseEvent *event);
       void mouseReleaseEvent(QMouseEvent *event);
};

#endif /* IMGLABEL_H_ */
