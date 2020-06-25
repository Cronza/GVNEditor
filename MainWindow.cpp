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
MainWindow::MainWindow() : QMainWindow()
{
    //Generate the UI C++ from the .ui XML form. Build objects from each of the .ui form widgets
    setupUi(this);

    //----------------- INTERACTIVITY ---------------------

    //Setup functionality for exiting the program
    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    //Setup functionality for menu bar options
    connect(insertRowAction, &QAction::triggered, this, &MainWindow::insertRow);
    connect(removeRowAction, &QAction::triggered, this, &MainWindow::removeRow);
}

void MainWindow::LoadFile(QString filePath)
{
    //Create the headers for the table using the 'tr()' localization functions
    QStringList headers;
    headers << tr("Speaker"); //Needs investigating into why tr doesnt work when this isnt a static class
    headers << tr("Dialogue"); //Needs investigating into why tr doesnt work when this isnt a static class

    //Read a dialogue file in
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);

    //Create the main table object, and pass in the text read in from the demo dialogue file
    ChapterTable *table = new ChapterTable(headers, file.readAll());
    file.close();

    //Set the data model used by the view
    view->setModel(table);

    //Resize each column based on the size of its contents
    for (int column = 0; column < table->columnCount(); ++column)
        view->resizeColumnToContents(column);
}

///Adds a row under of the currently selected row
void MainWindow::insertRow()
{
    //Grab references to the data model and selected item
    QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();

    //Create the row, and check whether it was successfully created
    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    //Loop through each column,
    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
    }

}

///Removes the User Selected Row from the table
void MainWindow::removeRow()
{
    //Grab the currently selected row
    QModelIndex index = view->selectionModel()->currentIndex();

    //Grab a reference to the view model
    QAbstractItemModel *model = view->model();

    //Ask the model to remove the row
    model->removeRow(index.row(), index.parent());
}
