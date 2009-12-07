#ifndef CONTROLSWINDOW_H
#define CONTROLSWINDOW_H

#include <QtGui/QDialog>
#include "../ui_controlswindow.h"

class Qcorr; // using this friend class

/** @ingroup classes */
/** @class ControlsWindow "src/controlswindow.h"
 * @brief  allows to modify parameters for the correlation operations, such as template size and scan interval. This class is a friend of Qcorr.
 */
class ControlsWindow : public QDialog
{
   Q_OBJECT

   public:
      ControlsWindow(Qcorr *parentWindow, QWidget *parent = 0); ///< Constructor of ControlsWindow class must point to a Qcorr parentWindow
      ~ControlsWindow(); ///< Closes and Destroys itself

      /** @brief  Enables/Disables control spinBoxes
       * @param bEnable boolean flag to enable or disable the spinBoxes for controlling correlation parameters of the Qcorr class
       */
      void
      setEnableSpinBoxes(bool bEnable); ///< Set enable spinBoxes including the maximum values based on the m_parentWindow's size of its right image

      /** @brief  to obtain the scan Interval set in the spin box
       * @returns the scan interval value (in pixels)
       */
      int
      getScanInterval()
      {
         return m_nScanInterval;
      }
      ;

      /** @brief  to obtain the template's size value (as width) set in the spin box
       * @returns the scan template's size value (in pixels)
       */
      int
      getTemplateSize()
      {
         return m_nTemplateSize;
      }
      ;

   private Q_SLOTS:
      void
      setScanInterval(int nValue); ///< Q_SLOT that sets scan interval parameter in its friend Qcorr class according to the corresponding spinBox's value.
      void
      setTemplateSize(int nValue); ///< Q_SLOT that sets template size parameter in its friend Qcorr class according to the corresponding spinBox's value.

   private:
      Ui::ControlsWindowClass ui; ///< The Qt GUI form for this class, so its widgets can be accessed and manipulated.
      void
      createActions(); ///< Create Signal-Slot connections
      void
      updateParentStatusLabel(); ///< Updates Parent's status bar with the corresponding values from the control spin boxes.

      Qcorr *m_parentWindow; ///< Pointer to Main Window Object
      int m_nScanInterval; ///< interval of scan traversal by the template
      int m_nTemplateSize; ///< the template's size (for the width)
};

#endif // CONTROLSWINDOW_H
