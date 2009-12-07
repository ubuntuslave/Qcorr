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

/** @ingroup classes */
/** @class TargetImgLabel "src/targetImgLabel.h"
 * @brief  A sub-classed label widget implemented with the purpose of displaying the target image on the right panel.
 *
 * A sub-classed label widget implemented with the purpose of displaying the target image in the right panel with added functionality such as the enclosing match visualization and overlaid correlation map images
 */
class TargetImgLabel : public QLabel
{
   Q_OBJECT

   public:
      TargetImgLabel(QWidget *parent = 0);   ///< Constructor for the TargetImgLabel class
      virtual
      ~TargetImgLabel();

      /** @brief  Sets background image on this TargetImgLabel class
          * @param labelImage Pointer to a QImage instance that will be used as the label's background
          */
      void setImage(const QImage &labelImage);

      /** @brief  Overlays an Image ontop of the current one.
          * @param otherImage Pointer to a QImage instance that will overlay the current one using Qt::CompositionMode_Screen mode
          * @param nXoffset X offset for overlay image. Default is 0
          * @param nYoffset Y offset for overlay image. Default is 0
          */
      void overlayImage(const QImage &otherImage, int nXoffset = 0, int nYoffset = 0);

      /** @brief  Draws a dashed, green rectangle to indicate the position of a matching template on the target image
          * @param originPoint A QPoint that indicates the top-left coordinates of the matching rectangle
          * @param rectSize A QSize for the matching rectangle to be drawn
          */
      void drawEnclosedMatch(const QPoint originPoint, const QSize rectSize);

      /** @brief  Erases the green rectangle that indicated a matching template on the target image
          */
      void eraseEnclosedMatch();

   private:
      QImage *m_image;  ///< the right image (a.k.a target image)
      QImage *m_overlayImage; ///< the overlaid correlation map image
      QPoint m_originPoint;   ///< the point that indicates the top-left coordinates of the matching rectangle
      QSize m_rectSize; ///< the size of the enclosing match rectangle
      int m_nXoffset;   ///< X offset for overlay image
      int m_nYoffset;   ///< Y offset for overlay image

      bool m_bHasCorrResults; ///< indicates whether correlation results exist so an overlaid image can be composed on top of the target image
      bool m_bHasImage; ///< indicates whether this TargetImgLabel class has a target (main) image
      bool m_bHasOverlayImage;   ///< indicates whether this TargetImgLabel class has an overlaid image (Usually, a correlation results map)

   protected:
      /** @brief  Handles the paint events by refreshing/updating the contents of this TargetImgLabel class
          */
      void paintEvent(QPaintEvent * /* event */);

};

#endif /* TARGETIMGLABEL_H_ */
