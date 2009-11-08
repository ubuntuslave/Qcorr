/********************************************************************************
** Form generated from reading ui file 'qcorr.ui'
**
** Created: Sat Nov 7 21:09:07 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_QCORR_H
#define UI_QCORR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QcorrClass
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *left_verticalLayout;
    QHBoxLayout *leftImg_horizontalLayout;
    QLineEdit *leftImage_lineEdit;
    QPushButton *leftBrowse_pushButton;
    QLabel *leftImage_label;
    QSpacerItem *verticalSpacer;
    QWidget *layoutWidget1;
    QVBoxLayout *right_verticalLayout;
    QHBoxLayout *leftImg_horizontalLayout_2;
    QLineEdit *rightImage_lineEdit;
    QPushButton *rightBrowse_pushButton;
    QLabel *rightImage_label;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *corr_pushButton;
    QLabel *corrResults_label;
    QSpacerItem *horizontalSpacer;
    QPushButton *quit_pushButton;
    QMenuBar *menubar;
    QMenu *menu_Menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QcorrClass)
    {
        if (QcorrClass->objectName().isEmpty())
            QcorrClass->setObjectName(QString::fromUtf8("QcorrClass"));
        QcorrClass->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QcorrClass->sizePolicy().hasHeightForWidth());
        QcorrClass->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(QcorrClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 791, 551));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        splitter = new QSplitter(widget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setFrameShape(QFrame::Panel);
        splitter->setFrameShadow(QFrame::Plain);
        splitter->setMidLineWidth(1);
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        left_verticalLayout = new QVBoxLayout(layoutWidget);
        left_verticalLayout->setObjectName(QString::fromUtf8("left_verticalLayout"));
        left_verticalLayout->setContentsMargins(0, 0, 0, 0);
        leftImg_horizontalLayout = new QHBoxLayout();
        leftImg_horizontalLayout->setSpacing(0);
        leftImg_horizontalLayout->setObjectName(QString::fromUtf8("leftImg_horizontalLayout"));
        leftImg_horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        leftImage_lineEdit = new QLineEdit(layoutWidget);
        leftImage_lineEdit->setObjectName(QString::fromUtf8("leftImage_lineEdit"));

        leftImg_horizontalLayout->addWidget(leftImage_lineEdit);

        leftBrowse_pushButton = new QPushButton(layoutWidget);
        leftBrowse_pushButton->setObjectName(QString::fromUtf8("leftBrowse_pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(leftBrowse_pushButton->sizePolicy().hasHeightForWidth());
        leftBrowse_pushButton->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        leftBrowse_pushButton->setFont(font);

        leftImg_horizontalLayout->addWidget(leftBrowse_pushButton);


        left_verticalLayout->addLayout(leftImg_horizontalLayout);

        leftImage_label = new QLabel(layoutWidget);
        leftImage_label->setObjectName(QString::fromUtf8("leftImage_label"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(leftImage_label->sizePolicy().hasHeightForWidth());
        leftImage_label->setSizePolicy(sizePolicy2);
        leftImage_label->setCursor(QCursor(Qt::ArrowCursor));
        leftImage_label->setMouseTracking(false);
        leftImage_label->setFocusPolicy(Qt::NoFocus);
        leftImage_label->setScaledContents(false);

        left_verticalLayout->addWidget(leftImage_label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        left_verticalLayout->addItem(verticalSpacer);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        right_verticalLayout = new QVBoxLayout(layoutWidget1);
        right_verticalLayout->setObjectName(QString::fromUtf8("right_verticalLayout"));
        right_verticalLayout->setContentsMargins(0, 0, 0, 0);
        leftImg_horizontalLayout_2 = new QHBoxLayout();
        leftImg_horizontalLayout_2->setObjectName(QString::fromUtf8("leftImg_horizontalLayout_2"));
        rightImage_lineEdit = new QLineEdit(layoutWidget1);
        rightImage_lineEdit->setObjectName(QString::fromUtf8("rightImage_lineEdit"));

        leftImg_horizontalLayout_2->addWidget(rightImage_lineEdit);

        rightBrowse_pushButton = new QPushButton(layoutWidget1);
        rightBrowse_pushButton->setObjectName(QString::fromUtf8("rightBrowse_pushButton"));
        sizePolicy1.setHeightForWidth(rightBrowse_pushButton->sizePolicy().hasHeightForWidth());
        rightBrowse_pushButton->setSizePolicy(sizePolicy1);
        rightBrowse_pushButton->setFont(font);

        leftImg_horizontalLayout_2->addWidget(rightBrowse_pushButton);


        right_verticalLayout->addLayout(leftImg_horizontalLayout_2);

        rightImage_label = new QLabel(layoutWidget1);
        rightImage_label->setObjectName(QString::fromUtf8("rightImage_label"));
        sizePolicy2.setHeightForWidth(rightImage_label->sizePolicy().hasHeightForWidth());
        rightImage_label->setSizePolicy(sizePolicy2);
        rightImage_label->setScaledContents(false);

        right_verticalLayout->addWidget(rightImage_label);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        right_verticalLayout->addItem(verticalSpacer_2);

        splitter->addWidget(layoutWidget1);

        verticalLayout->addWidget(splitter);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        corr_pushButton = new QPushButton(widget);
        corr_pushButton->setObjectName(QString::fromUtf8("corr_pushButton"));

        horizontalLayout->addWidget(corr_pushButton);

        corrResults_label = new QLabel(widget);
        corrResults_label->setObjectName(QString::fromUtf8("corrResults_label"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(corrResults_label->sizePolicy().hasHeightForWidth());
        corrResults_label->setSizePolicy(sizePolicy3);
        corrResults_label->setAutoFillBackground(true);
        corrResults_label->setScaledContents(true);

        horizontalLayout->addWidget(corrResults_label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        quit_pushButton = new QPushButton(widget);
        quit_pushButton->setObjectName(QString::fromUtf8("quit_pushButton"));

        horizontalLayout->addWidget(quit_pushButton);


        verticalLayout->addLayout(horizontalLayout);

        QcorrClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QcorrClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menu_Menu = new QMenu(menubar);
        menu_Menu->setObjectName(QString::fromUtf8("menu_Menu"));
        QcorrClass->setMenuBar(menubar);
        statusbar = new QStatusBar(QcorrClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        QcorrClass->setStatusBar(statusbar);
        QWidget::setTabOrder(leftImage_lineEdit, leftBrowse_pushButton);
        QWidget::setTabOrder(leftBrowse_pushButton, rightImage_lineEdit);
        QWidget::setTabOrder(rightImage_lineEdit, rightBrowse_pushButton);

        menubar->addAction(menu_Menu->menuAction());

        retranslateUi(QcorrClass);

        QMetaObject::connectSlotsByName(QcorrClass);
    } // setupUi

    void retranslateUi(QMainWindow *QcorrClass)
    {
        QcorrClass->setWindowTitle(QApplication::translate("QcorrClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        leftBrowse_pushButton->setText(QApplication::translate("QcorrClass", "Browse &Left Image", 0, QApplication::UnicodeUTF8));
        leftImage_label->setText(QString());
        rightBrowse_pushButton->setText(QApplication::translate("QcorrClass", "Browse &Right Image", 0, QApplication::UnicodeUTF8));
        rightImage_label->setText(QString());
        corr_pushButton->setText(QApplication::translate("QcorrClass", "&Correlate", 0, QApplication::UnicodeUTF8));
        corrResults_label->setText(QString());
        quit_pushButton->setText(QApplication::translate("QcorrClass", "&Quit", 0, QApplication::UnicodeUTF8));
        menu_Menu->setTitle(QApplication::translate("QcorrClass", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QcorrClass: public Ui_QcorrClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCORR_H
