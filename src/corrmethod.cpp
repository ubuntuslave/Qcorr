#include "corrmethod.h"
#include "globals.h"

CorrMethod::CorrMethod(QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	this->setMinimumSize(ui.dialog_Frame->size());

	m_nChosenMethod = N0_CORR_METHOD;

	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(cancelMethod()));
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(chooseMethod()));
}

CorrMethod::~CorrMethod()
{

}

/** @brief Retrieve the selected method to be used in the correlation process
 *  @returns selected correlation method (from global enumeration defined in globals.h)
 */
int CorrMethod::getMethod()
{
   return m_nChosenMethod;
}


// begin Q_SLOTS vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void CorrMethod::cancelMethod(){
      m_nChosenMethod = N0_CORR_METHOD;
      emit reject();
}

void CorrMethod::chooseMethod(){

   if(ui.method1_radioButton->isChecked())
      {
      m_nChosenMethod = CROSS_CORR;
      emit accept();
      }
   else if(ui.method2_radioButton->isChecked())
      {
      m_nChosenMethod = SUM_SQ_DIFF;
      emit accept();
      }
   else if(ui.method3_radioButton->isChecked())
      {
      m_nChosenMethod = CORR_COEFF;
      emit accept();
      }
   else
      m_nChosenMethod = N0_CORR_METHOD;
}


// end Q_SLOTS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
