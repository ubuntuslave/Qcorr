/*
 * imgLabel.h
 *
 *  Created on: Nov 11, 2009
 *      Author: carlos
 *
 *  Description: Sub-classing QLabel in order to allow higher control of mouse-event positions and other properties.
 */

#ifndef IMGLABEL_H_
#define IMGLABEL_H_

#include <QtGui/QLabel>
class QRubberBand;
class QPoint;

class Qcorr; // using this friend class

/** @ingroup classes */
/** @class ImgLabel "src/imgLabel.h"
 *  @brief  A sub-classed label widget implemented with the purpose of displaying the reference image on the left  panel.
 *
 *  A sub-classed label widget implemented with the purpose of displaying the reference image on the left panel with added functionality such as the rubberBand selection and coordinate tracking of the mouse pointer.
 */
class ImgLabel : public QLabel
{
   Q_OBJECT

   public:
      ImgLabel(Qcorr *parentWindow, QWidget *parent = 0); ///< Constructor of ImgLabel class must point to a Qcorr parentWindow

      virtual
      ~ImgLabel();

      /** @brief Allows to enable/disable the ImgLabel's rubberBand selection functionality.
       * @param bHasRubberBand boolean flag to enable or disable the rubberBand selection functionality.
       */
      void
      setSelectable(bool bHasRubberBand);

   private:
      friend class Qcorr; ///< Qcorr is a friend class of this ImgLabel class, so all members from ImgLabel are accessible by a Qcorr object

      Qcorr *m_parentWindow; ///< Pointer to Main Window Object (There should be only one on these)

      QRubberBand *m_rubberBand; ///< the rubberBand object.
      QPoint m_originPoint; ///< rubberBand's top-left corner point
      QPoint m_finalPoint; ///< rubberBand's bottom-right corner point
      QPoint m_currentPressedPoint; ///< the coordinates of the current mouse pointer when it's pressed (held-down)

      QPoint m_labelUpperLeftCornerPoint; ///< Top-left corner of the label
      QPoint m_labelLowerRightCornerPoint; ///< Bottom-right corner of the label
      QPoint m_mousePosPoint1; ///< First mouse position point of the template selection
      QPoint m_mousePosPoint2; ///< Final mouse position point of the template selection

      bool m_bMouseIsPressed; ///< indicates whether the mouse is currently being pressed (held-down)
      bool m_bStartedTemplateSelection; ///< indicates whether the template selection has begun
      bool m_bMouseInTemplateRegion; ///< indicates whether the mouse pointer is inside the rubberBand selection area
      bool m_bMouseAtTemplateTopEdge; ///< indicates whether the mouse pointer is at the top edge of the rubberBand selection area
      bool m_bMouseAtTemplateBottomEdge; ///< indicates whether the mouse pointer is at the bottom edge of the rubberBand selection area
      bool m_bMouseAtTemplateLeftEdge; ///< indicates whether the mouse pointer is at the left edge of the rubberBand selection area
      bool m_bMouseAtTemplateRightEdge; ///< indicates whether the mouse pointer is at the right edge of the rubberBand selection area
      bool m_bHasRubberBand; ///< indicates whether the rubberBand is enabled/disabled.

      int m_nXNewPos; ///< X-value used in the rubberBand movement
      int m_nYNewPos; ///< Y-value used in the rubberBand movement

      /** @brief Sets a group of flags used for the mouse pointer in relation to the template's region and edges.
       * @param bStatus template region's status
       */
      void
      setTemplateFlags(bool bStatus);

      /** @brief Used to check the mouse pointer in relation to the template's region and edges.
       * @param mouseX X-coordinates of the mouse pointer
       * @param mouseY Y-coordinates of the mouse pointer
       */
      void
      checkTemplateRegions(int mouseX, int mouseY);

      /** @brief Displays the XY-coordinates of the mouse pointer on the status bar
       * Displays the XY-coordinates of the mouse pointer (relative to the ImgLabel) in the status bar of the friend-parent's main window. It only display the mouse pointer coordinate information if rubberBand actions are enabled
       * @param point0 the coordinates of the origin point of the rubberBand selection
       * @param point1 the coordinates of the final point of the rubberBand selection
       */
      void
      displayCoordinatesOnStatusLabel(QPoint &point0, QPoint &point1);

   protected:
      void
      mousePressEvent(QMouseEvent *event); ///< press mouse event handler
      void
      mouseMoveEvent(QMouseEvent *event); ///< move mouse event handler
      void
      mouseReleaseEvent(QMouseEvent *event); ///< release mouse event handler
};

#endif /* IMGLABEL_H_ */
