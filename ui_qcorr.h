/********************************************************************************
** Form generated from reading ui file 'qcorr.ui'
**
** Created: Mon Nov 30 17:08:58 2009
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
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QcorrClass
{
public:
    QAction *action_Quit;
    QAction *action_Correlation_Map;
    QAction *actionTemplate_Matching;
    QAction *action_Disparity_Finder;
    QWidget *centralwidget;
    QFrame *main_frame;
    QVBoxLayout *main_verticalLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *left_verticalLayout;
    QHBoxLayout *leftImg_horizontalLayout;
    QLineEdit *leftImage_lineEdit;
    QPushButton *leftBrowse_pushButton;
    QScrollArea *leftImage_scrollArea;
    QWidget *scrollAreaWidgetContents_3;
    QWidget *layoutWidget1;
    QVBoxLayout *right_verticalLayout;
    QHBoxLayout *rightImg_horizontalLayout;
    QLineEdit *rightImage_lineEdit;
    QPushButton *rightBrowse_pushButton;
    QScrollArea *rightImage_scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QHBoxLayout *bottom_horizontalLayout;
    QPushButton *start_pushButton;
    QLabel *corrResults_label;
    QSpacerItem *horizontalSpacer;
    QPushButton *quit_pushButton;
    QMenuBar *menubar;
    QMenu *menu_Menu;
    QMenu *menu_View;
    QMenu *menu_Mode;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QcorrClass)
    {
        if (QcorrClass->objectName().isEmpty())
            QcorrClass->setObjectName(QString::fromUtf8("QcorrClass"));
        QcorrClass->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(QcorrClass->sizePolicy().hasHeightForWidth());
        QcorrClass->setSizePolicy(sizePolicy);
        action_Quit = new QAction(QcorrClass);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Correlation_Map = new QAction(QcorrClass);
        action_Correlation_Map->setObjectName(QString::fromUtf8("action_Correlation_Map"));
        action_Correlation_Map->setCheckable(true);
        action_Correlation_Map->setEnabled(false);
        actionTemplate_Matching = new QAction(QcorrClass);
        actionTemplate_Matching->setObjectName(QString::fromUtf8("actionTemplate_Matching"));
        actionTemplate_Matching->setCheckable(true);
        action_Disparity_Finder = new QAction(QcorrClass);
        action_Disparity_Finder->setObjectName(QString::fromUtf8("action_Disparity_Finder"));
        action_Disparity_Finder->setCheckable(true);
        centralwidget = new QWidget(QcorrClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        main_frame = new QFrame(centralwidget);
        main_frame->setObjectName(QString::fromUtf8("main_frame"));
        main_frame->setGeometry(QRect(1, 0, 791, 541));
        main_verticalLayout = new QVBoxLayout(main_frame);
        main_verticalLayout->setObjectName(QString::fromUtf8("main_verticalLayout"));
        main_verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        splitter = new QSplitter(main_frame);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
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
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(leftBrowse_pushButton->sizePolicy().hasHeightForWidth());
        leftBrowse_pushButton->setSizePolicy(sizePolicy2);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        leftBrowse_pushButton->setFont(font);

        leftImg_horizontalLayout->addWidget(leftBrowse_pushButton);


        left_verticalLayout->addLayout(leftImg_horizontalLayout);

        leftImage_scrollArea = new QScrollArea(layoutWidget);
        leftImage_scrollArea->setObjectName(QString::fromUtf8("leftImage_scrollArea"));
        leftImage_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        leftImage_scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 255, 224));
        leftImage_scrollArea->setWidget(scrollAreaWidgetContents_3);

        left_verticalLayout->addWidget(leftImage_scrollArea);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        right_verticalLayout = new QVBoxLayout(layoutWidget1);
        right_verticalLayout->setObjectName(QString::fromUtf8("right_verticalLayout"));
        right_verticalLayout->setContentsMargins(0, 0, 0, 0);
        rightImg_horizontalLayout = new QHBoxLayout();
        rightImg_horizontalLayout->setSpacing(0);
        rightImg_horizontalLayout->setObjectName(QString::fromUtf8("rightImg_horizontalLayout"));
        rightImage_lineEdit = new QLineEdit(layoutWidget1);
        rightImage_lineEdit->setObjectName(QString::fromUtf8("rightImage_lineEdit"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(rightImage_lineEdit->sizePolicy().hasHeightForWidth());
        rightImage_lineEdit->setSizePolicy(sizePolicy3);

        rightImg_horizontalLayout->addWidget(rightImage_lineEdit);

        rightBrowse_pushButton = new QPushButton(layoutWidget1);
        rightBrowse_pushButton->setObjectName(QString::fromUtf8("rightBrowse_pushButton"));
        sizePolicy2.setHeightForWidth(rightBrowse_pushButton->sizePolicy().hasHeightForWidth());
        rightBrowse_pushButton->setSizePolicy(sizePolicy2);
        rightBrowse_pushButton->setFont(font);

        rightImg_horizontalLayout->addWidget(rightBrowse_pushButton);


        right_verticalLayout->addLayout(rightImg_horizontalLayout);

        rightImage_scrollArea = new QScrollArea(layoutWidget1);
        rightImage_scrollArea->setObjectName(QString::fromUtf8("rightImage_scrollArea"));
        rightImage_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        rightImage_scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 255, 224));
        rightImage_scrollArea->setWidget(scrollAreaWidgetContents_2);

        right_verticalLayout->addWidget(rightImage_scrollArea);

        splitter->addWidget(layoutWidget1);

        main_verticalLayout->addWidget(splitter);

        bottom_horizontalLayout = new QHBoxLayout();
        bottom_horizontalLayout->setSpacing(0);
        bottom_horizontalLayout->setObjectName(QString::fromUtf8("bottom_horizontalLayout"));
        start_pushButton = new QPushButton(main_frame);
        start_pushButton->setObjectName(QString::fromUtf8("start_pushButton"));

        bottom_horizontalLayout->addWidget(start_pushButton);

        corrResults_label = new QLabel(main_frame);
        corrResults_label->setObjectName(QString::fromUtf8("corrResults_label"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(corrResults_label->sizePolicy().hasHeightForWidth());
        corrResults_label->setSizePolicy(sizePolicy4);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(11);
        corrResults_label->setFont(font1);
        corrResults_label->setAutoFillBackground(true);
        corrResults_label->setScaledContents(true);

        bottom_horizontalLayout->addWidget(corrResults_label);

        horizontalSpacer = new QSpacerItem(5, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        bottom_horizontalLayout->addItem(horizontalSpacer);

        quit_pushButton = new QPushButton(main_frame);
        quit_pushButton->setObjectName(QString::fromUtf8("quit_pushButton"));

        bottom_horizontalLayout->addWidget(quit_pushButton);


        main_verticalLayout->addLayout(bottom_horizontalLayout);

        QcorrClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QcorrClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        menu_Menu = new QMenu(menubar);
        menu_Menu->setObjectName(QString::fromUtf8("menu_Menu"));
        menu_View = new QMenu(menubar);
        menu_View->setObjectName(QString::fromUtf8("menu_View"));
        menu_Mode = new QMenu(menubar);
        menu_Mode->setObjectName(QString::fromUtf8("menu_Mode"));
        QcorrClass->setMenuBar(menubar);
        statusbar = new QStatusBar(QcorrClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        QcorrClass->setStatusBar(statusbar);

        menubar->addAction(menu_Menu->menuAction());
        menubar->addAction(menu_View->menuAction());
        menubar->addAction(menu_Mode->menuAction());
        menu_Menu->addAction(action_Quit);
        menu_View->addAction(action_Correlation_Map);
        menu_Mode->addAction(actionTemplate_Matching);
        menu_Mode->addAction(action_Disparity_Finder);

        retranslateUi(QcorrClass);

        QMetaObject::connectSlotsByName(QcorrClass);
    } // setupUi

    void retranslateUi(QMainWindow *QcorrClass)
    {
        QcorrClass->setWindowTitle(QApplication::translate("QcorrClass", "QCorr", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("QcorrClass", "&Quit", 0, QApplication::UnicodeUTF8));
        action_Correlation_Map->setText(QApplication::translate("QcorrClass", "&Correlation Map", 0, QApplication::UnicodeUTF8));
        actionTemplate_Matching->setText(QApplication::translate("QcorrClass", "Template &Matching", 0, QApplication::UnicodeUTF8));
        action_Disparity_Finder->setText(QApplication::translate("QcorrClass", "&Disparity Finder", 0, QApplication::UnicodeUTF8));
        leftBrowse_pushButton->setText(QApplication::translate("QcorrClass", "Browse &Left Image", 0, QApplication::UnicodeUTF8));
        rightBrowse_pushButton->setText(QApplication::translate("QcorrClass", "Browse &Right Image", 0, QApplication::UnicodeUTF8));
        start_pushButton->setText(QApplication::translate("QcorrClass", "&Start", 0, QApplication::UnicodeUTF8));
        corrResults_label->setText(QString());
        quit_pushButton->setText(QApplication::translate("QcorrClass", "&Quit", 0, QApplication::UnicodeUTF8));
        menu_Menu->setTitle(QApplication::translate("QcorrClass", "&File", 0, QApplication::UnicodeUTF8));
        menu_View->setTitle(QApplication::translate("QcorrClass", "&View", 0, QApplication::UnicodeUTF8));
        menu_Mode->setTitle(QApplication::translate("QcorrClass", "&Mode", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QcorrClass: public Ui_QcorrClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCORR_H
