/********************************************************************************
** Form generated from reading UI file 'TEST.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TEST
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *header;
    QLabel *version;
    QLabel *title;
    QSpacerItem *horizontalSpacer;
    QFrame *headerBottomBorder;
    QGridLayout *gridLayout;
    QSplitter *storyTitle;
    QLabel *titleLabel;
    QLineEdit *lineEdit;
    QSplitter *storyAuthor;
    QLabel *titleLabel_3;
    QLineEdit *lineEdit_3;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TEST)
    {
        if (TEST->objectName().isEmpty())
            TEST->setObjectName(QString::fromUtf8("TEST"));
        TEST->resize(943, 450);
        centralWidget = new QWidget(TEST);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        header = new QHBoxLayout();
        header->setSpacing(6);
        header->setObjectName(QString::fromUtf8("header"));
        header->setSizeConstraint(QLayout::SetDefaultConstraint);
        version = new QLabel(centralWidget);
        version->setObjectName(QString::fromUtf8("version"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(version->sizePolicy().hasHeightForWidth());
        version->setSizePolicy(sizePolicy);
        version->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("Terminal"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        version->setFont(font);

        header->addWidget(version);

        title = new QLabel(centralWidget);
        title->setObjectName(QString::fromUtf8("title"));
        sizePolicy.setHeightForWidth(title->sizePolicy().hasHeightForWidth());
        title->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Terminal"));
        font1.setPointSize(12);
        font1.setItalic(false);
        title->setFont(font1);

        header->addWidget(title);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        header->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(header);

        headerBottomBorder = new QFrame(centralWidget);
        headerBottomBorder->setObjectName(QString::fromUtf8("headerBottomBorder"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(headerBottomBorder->sizePolicy().hasHeightForWidth());
        headerBottomBorder->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(false);
        font2.setWeight(50);
        headerBottomBorder->setFont(font2);
        headerBottomBorder->setFrameShadow(QFrame::Plain);
        headerBottomBorder->setLineWidth(2);
        headerBottomBorder->setFrameShape(QFrame::HLine);

        verticalLayout_2->addWidget(headerBottomBorder);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        storyTitle = new QSplitter(centralWidget);
        storyTitle->setObjectName(QString::fromUtf8("storyTitle"));
        storyTitle->setLineWidth(1);
        storyTitle->setOrientation(Qt::Horizontal);
        storyTitle->setHandleWidth(5);
        titleLabel = new QLabel(storyTitle);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        sizePolicy.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy);
        titleLabel->setMinimumSize(QSize(0, 0));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Terminal"));
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        titleLabel->setFont(font3);
        storyTitle->addWidget(titleLabel);
        lineEdit = new QLineEdit(storyTitle);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        storyTitle->addWidget(lineEdit);

        gridLayout->addWidget(storyTitle, 0, 0, 1, 1);

        storyAuthor = new QSplitter(centralWidget);
        storyAuthor->setObjectName(QString::fromUtf8("storyAuthor"));
        storyAuthor->setOrientation(Qt::Horizontal);
        titleLabel_3 = new QLabel(storyAuthor);
        titleLabel_3->setObjectName(QString::fromUtf8("titleLabel_3"));
        sizePolicy.setHeightForWidth(titleLabel_3->sizePolicy().hasHeightForWidth());
        titleLabel_3->setSizePolicy(sizePolicy);
        titleLabel_3->setMinimumSize(QSize(0, 0));
        titleLabel_3->setFont(font3);
        storyAuthor->addWidget(titleLabel_3);
        lineEdit_3 = new QLineEdit(storyAuthor);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        sizePolicy2.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy2);
        storyAuthor->addWidget(lineEdit_3);

        gridLayout->addWidget(storyAuthor, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        TEST->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TEST);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 943, 22));
        TEST->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TEST);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TEST->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TEST);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TEST->setStatusBar(statusBar);
        QWidget::setTabOrder(lineEdit, lineEdit_3);

        retranslateUi(TEST);

        QMetaObject::connectSlotsByName(TEST);
    } // setupUi

    void retranslateUi(QMainWindow *TEST)
    {
        TEST->setWindowTitle(QApplication::translate("TEST", "TEST", nullptr));
        version->setText(QApplication::translate("TEST", "StoryBuilder", nullptr));
        title->setText(QApplication::translate("TEST", "v.1.0", nullptr));
        titleLabel->setText(QApplication::translate("TEST", "Story Title:", nullptr));
        titleLabel_3->setText(QApplication::translate("TEST", "Story Author:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TEST: public Ui_TEST {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
