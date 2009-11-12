/*
 * imgLabel.h
 *
 *  Created on: Nov 11, 2009
 *      Author: carlos
 */

#ifndef IMGLABEL_H_
#define IMGLABEL_H_

#include <QtGui/QLabel>
class QMainWindow;
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

      QPoint *m_pixelPoint;

      int m_xpos, m_ypos;

   protected:
       void mousePressEvent(QMouseEvent *event);
};

#endif /* IMGLABEL_H_ */
