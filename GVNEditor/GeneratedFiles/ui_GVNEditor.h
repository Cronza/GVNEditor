/********************************************************************************
** Form generated from reading UI file 'GVNEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GVNEDITOR_H
#define UI_GVNEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GVNEditorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GVNEditorClass)
    {
        if (GVNEditorClass->objectName().isEmpty())
            GVNEditorClass->setObjectName(QString::fromUtf8("GVNEditorClass"));
        GVNEditorClass->resize(600, 400);
        menuBar = new QMenuBar(GVNEditorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        GVNEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GVNEditorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        GVNEditorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(GVNEditorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        GVNEditorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GVNEditorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GVNEditorClass->setStatusBar(statusBar);

        retranslateUi(GVNEditorClass);

        QMetaObject::connectSlotsByName(GVNEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *GVNEditorClass)
    {
        GVNEditorClass->setWindowTitle(QApplication::translate("GVNEditorClass", "GVNEditor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GVNEditorClass: public Ui_GVNEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GVNEDITOR_H
