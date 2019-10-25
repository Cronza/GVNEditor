/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/*This script uses generic model references to avoid dependencies on particular files*/

#include "MainWindow.h"
#include "StoryBuilder\ChapterTable.h"
#include "QDebug"
#include <QFile>

///Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Generate the UI C++ from the .ui XML form
    setupUi(this);

    //Create the headers for the table using the 'tr()' localization functions
    QStringList headers;
    headers << tr("Speaker");
    headers << tr("Dialogue");

    //Read a demo dialogue file in
    QFile file(":/default.txt");
    file.open(QIODevice::ReadOnly);

    //Create the main table object, and pass in the text read in from the demo dialogue file
    ChapterTable *table = new ChapterTable(headers, file.readAll());
    file.close();

    //Set the data model used by the view
    view->setModel(table);

    //Resize each column based on the size of its contents
    for (int column = 0; column < table->columnCount(); ++column)
        view->resizeColumnToContents(column);

    //----------------- INTERACTIVITY ---------------------

    //Setup functionality for exiting the program
    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    //Setup functionality for selecting elements in the table
    connect(view->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &MainWindow::updateActions);

    //Setup functionality for menu bar options
    connect(actionsMenu, &QMenu::aboutToShow, this, &MainWindow::updateActions);
    connect(insertRowAction, &QAction::triggered, this, &MainWindow::insertRow);
    connect(removeRowAction, &QAction::triggered, this, &MainWindow::removeRow);

    //Tell Qt to recognize the new connections
    updateActions();
}

///Create a child item under the currently selected item
//void MainWindow::insertChild()
//{
//    //Grab references to the data model and selected item
//    QModelIndex index = view->selectionModel()->currentIndex();
//    QAbstractItemModel *model = view->model();
//
//    //Are there any columns currently? If not, add an initial one
//    if (model->columnCount(index) == 0) {
//        if (!model->insertColumn(0, index))
//            return;
//    }
//
//    //Are there any rows currently? If not, add an initial one
//    if (!model->insertRow(0, index))
//        return;
//
//    //Loop through each column, adding a child item to each under the selected item
//    for (int column = 0; column < model->columnCount(index); ++column) {
//        QModelIndex child = model->index(0, column, index);
//        model->setData(child, QVariant("[No data]"), Qt::EditRole);
//
//        //if (!model->headerData(column, Qt::Horizontal).isValid())
//        //    model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
//    }
//
//    //Change selection to the new child item
//    view->selectionModel()->setCurrentIndex(model->index(0, 0, index),
//                                            QItemSelectionModel::ClearAndSelect);
//
//    //Update available actions
//    updateActions();
//}


///Adds a row under of the currently selected row
void MainWindow::insertRow()
{
    //Grab references to the data model and selected item
    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();

    //Create the row, and check whether it was successfully created
    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    //Update available actions
    updateActions();

    //Loop through each column,
    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
    }

}

void MainWindow::removeRow()
{
    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void MainWindow::updateActions()
{
    bool hasSelection = !view->selectionModel()->selection().isEmpty();
    removeRowAction->setEnabled(hasSelection);
    removeColumnAction->setEnabled(hasSelection);

    bool hasCurrent = view->selectionModel()->currentIndex().isValid();
    insertRowAction->setEnabled(hasCurrent);
    insertColumnAction->setEnabled(hasCurrent);

    if (hasCurrent) {
        view->closePersistentEditor(view->selectionModel()->currentIndex());

        int row = view->selectionModel()->currentIndex().row();
        int column = view->selectionModel()->currentIndex().column();
        if (view->selectionModel()->currentIndex().parent().isValid())
            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        else
            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    }
}
