/********************************************************************************
** Form generated from reading ui file 'corrmethod.ui'
**
** Created: Sun Dec 6 22:55:07 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CORRMETHOD_H
#define UI_CORRMETHOD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CorrMethodClass
{
public:
    QFrame *dialog_Frame;
    QVBoxLayout *verticalLayout;
    QLabel *selectMethod_label;
    QGroupBox *methods_groupBox;
    QRadioButton *method3_radioButton;
    QRadioButton *method2_radioButton;
    QRadioButton *method1_radioButton;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *CorrMethodClass)
    {
        if (CorrMethodClass->objectName().isEmpty())
            CorrMethodClass->setObjectName(QString::fromUtf8("CorrMethodClass"));
        CorrMethodClass->resize(247, 194);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CorrMethodClass->sizePolicy().hasHeightForWidth());
        CorrMethodClass->setSizePolicy(sizePolicy);
        CorrMethodClass->setModal(true);
        dialog_Frame = new QFrame(CorrMethodClass);
        dialog_Frame->setObjectName(QString::fromUtf8("dialog_Frame"));
        dialog_Frame->setGeometry(QRect(10, 10, 231, 181));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dialog_Frame->sizePolicy().hasHeightForWidth());
        dialog_Frame->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(dialog_Frame);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        selectMethod_label = new QLabel(dialog_Frame);
        selectMethod_label->setObjectName(QString::fromUtf8("selectMethod_label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        selectMethod_label->setFont(font);

        verticalLayout->addWidget(selectMethod_label);

        methods_groupBox = new QGroupBox(dialog_Frame);
        methods_groupBox->setObjectName(QString::fromUtf8("methods_groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(methods_groupBox->sizePolicy().hasHeightForWidth());
        methods_groupBox->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        methods_groupBox->setFont(font1);
        method3_radioButton = new QRadioButton(methods_groupBox);
        method3_radioButton->setObjectName(QString::fromUtf8("method3_radioButton"));
        method3_radioButton->setGeometry(QRect(10, 70, 211, 24));
        method2_radioButton = new QRadioButton(methods_groupBox);
        method2_radioButton->setObjectName(QString::fromUtf8("method2_radioButton"));
        method2_radioButton->setGeometry(QRect(10, 40, 211, 24));
        method1_radioButton = new QRadioButton(methods_groupBox);
        method1_radioButton->setObjectName(QString::fromUtf8("method1_radioButton"));
        method1_radioButton->setGeometry(QRect(10, 10, 131, 24));

        verticalLayout->addWidget(methods_groupBox);

        buttonBox = new QDialogButtonBox(dialog_Frame);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        verticalSpacer = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        QWidget::setTabOrder(method1_radioButton, method2_radioButton);
        QWidget::setTabOrder(method2_radioButton, method3_radioButton);
        QWidget::setTabOrder(method3_radioButton, buttonBox);

        retranslateUi(CorrMethodClass);

        QMetaObject::connectSlotsByName(CorrMethodClass);
    } // setupUi

    void retranslateUi(QDialog *CorrMethodClass)
    {
        CorrMethodClass->setWindowTitle(QApplication::translate("CorrMethodClass", "Correlation Methods", 0, QApplication::UnicodeUTF8));
        selectMethod_label->setText(QApplication::translate("CorrMethodClass", "Select Correlation Method:", 0, QApplication::UnicodeUTF8));
        methods_groupBox->setTitle(QString());
        method3_radioButton->setText(QApplication::translate("CorrMethodClass", "Correlation Coefficient", 0, QApplication::UnicodeUTF8));
        method2_radioButton->setText(QApplication::translate("CorrMethodClass", "Sum of Squared Differences", 0, QApplication::UnicodeUTF8));
        method1_radioButton->setText(QApplication::translate("CorrMethodClass", "Cross Correlation", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CorrMethodClass);
    } // retranslateUi

};

namespace Ui {
    class CorrMethodClass: public Ui_CorrMethodClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CORRMETHOD_H
