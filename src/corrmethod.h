#ifndef CORRMETHOD_H
#define CORRMETHOD_H

#include <QtGui/QDialog>
#include "../ui_corrmethod.h" // UIC is always spiting out this form header files on the root of the project folder

class CorrMethod : public QDialog
{
    Q_OBJECT

public:
    CorrMethod(QWidget *parent = 0);
    ~CorrMethod();

    /** @brief Retrieve the selected method to be used in the correlation process
     *  @returns selected correlation method (from global enumeration defined in globals.h)
     */
    int getMethod();

private Q_SLOTS:
    void cancelMethod();
    void chooseMethod();

private:
    int m_nChosenMethod;
    Ui::CorrMethodClass ui;
};

#endif // CORRMETHOD_H
