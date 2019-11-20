#ifndef CORRMETHOD_H
#define CORRMETHOD_H

#include <QDialog>
#include "../ui_corrmethod.h" // UIC is always spiting out this form header files on the root of the project folder
/** @ingroup classes */
/** @class CorrMethod "src/corrmethod.h"
 * @brief  Dialog to select a method in which the correlation "template matching" operation will be based upon.
 *    The available correlation methods are the following:
 *       - CROSS_CORR (cross correlation):
 *        \f[
 *             C(u,v) = \frac
 *                      {\sum{\left\{T(x,y) * I(x-u,y-v)\right\}}}
 *                      {\sqrt{ \sum{I(x-u,y-v)^2}}}
 *
 *        \f]
 *       - SUM_SQ_DIFF (sum of squared differences):
 *        \f[
 *             C(u,v) = \frac
 *                      {\sum{\left\{T(x,y)-I(x-u,y-v)\right\}^2}}
 *                      {\sqrt{\sum{I(x-u,y-v)^2}}}
 *        \f]
 *       - CORR_COEFF (correlation coefficient):
 *        \f[
 *             C(u,v) = \frac
 *                      {\sum{\left\{(T(x,y)-T_{avg}) * (I(x-u,y-v)-I_{avg})\right\}}}
 *                      {\sqrt{\sum{(T(x,y)-T_{avg})^2} * \sum{(I(x-u,y-v)-I_{avg})^2}}}
 *        \f]
 */
class CorrMethod : public QDialog
{
   Q_OBJECT

   public:
      CorrMethod(QWidget *parent = 0); ///< Constructor for the CorrMethod class
      ~CorrMethod();

      /** @brief Retrieve the selected method to be used in the correlation process
       *
       *  Returns the selected method in which the correlation "template matching" operation will be based upon.
       *  From the global enumeration MethodOfCorrelation,
       *  the available correlation methods are: N0_CORR_METHOD = 0, CROSS_CORR = 1, SUM_SQ_DIFF = 2, or CORR_COEFF = 3
       *
       *  @returns selected correlation method (from global enumeration MethodOfCorrelation defined in globals.h).
       *           The available correlation methods are: N0_CORR_METHOD = 0, CROSS_CORR = 1, SUM_SQ_DIFF = 2, or CORR_COEFF = 3
       */
      int
      getMethod();

   private Q_SLOTS:
      void
      cancelMethod(); ///< Q_SLOT to cancel the method selection dialog.
      void
      chooseMethod(); ///< Q_SLOT to store the method selection from the dialog.

   private:
      /** The selected method in which the correlation "template matching" operation will be based upon.
       *  From the global enumeration MethodOfCorrelation,
       *  the available correlation methods are: N0_CORR_METHOD = 0, CROSS_CORR = 1, SUM_SQ_DIFF = 2, or CORR_COEFF = 3
       */
      int m_nChosenMethod;

      Ui::CorrMethodClass ui; ///< The Qt GUI form for this class, so its widgets can be accessed and manipulated.
};

#endif // CORRMETHOD_H
