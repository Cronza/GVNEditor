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

#include "GVNEditor.h"
#include "StoryBuilder\ChapterTable.h"
#include "QDebug"
#include "QDateTime"
#include <QFile>
#include "Utilities\Logger.h"

///Constructor
GVNEditor::GVNEditor() : QMainWindow()
{
    //Generate the UI C++ from the .ui XML form. Build objects from each of the .ui form widgets
    setupUi(this);

    //----------------- INTERACTIVITY ---------------------
    //Setup functionality for menu bar options
    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    connect(loadStoryFileAction, &QAction::triggered, this, &GVNEditor::LoadStoryData);
    connect(saveStoryFileAsAction, &QAction::triggered, this, &GVNEditor::SaveStoryDataAs);

    connect(addEntryButton, SIGNAL (clicked()), this, SLOT(AddChapterTableRow()));
    connect(removeEntryButton, SIGNAL (clicked()), this, SLOT(RemoveChapterTableRow()));
    connect(moveEntryUpButton, SIGNAL (clicked()), this, SLOT(MoveChapterTableRowUp()));
    connect(moveEntryDownButton, SIGNAL (clicked()), this, SLOT(MoveChapterTableRowDown()));

    //Spawn the Logger
    logger = new Logger(logList);

    //Spawn the editing table
    CreateChapterTable();
    logger->Log("Created Editing Table");

    //Spawn the Outliner
    //outliner = new Outliner

    logger->Log("*** GVN Editor Initialized ***");

}
GVNEditor::~GVNEditor()
{
    //delete ui;
}

void GVNEditor::CreateChapterTable()
{
    //Log("Creating the Editing Table");


    table = new ChapterTable(this);
    table->logger = logger;

    //Initialize the table with some data
    QFile exampleFile(":/examples/Example_Story_Data.xml");
    table->InitializeTableData(exampleFile);

    chapterTableView->setModel(table);

    //Resize the dialogue column for maximum room
    chapterTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    chapterTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    chapterTableView->setWordWrap(true);
    chapterTableView->horizontalHeader()->setVisible(true);
    chapterTableView->verticalHeader()->setVisible(true);
    chapterTableView->show();
}

void GVNEditor::AddChapterTableRow()
{
    QModelIndex index = chapterTableView->selectionModel()->currentIndex();
    table->AddRow(index);

}

void GVNEditor::RemoveChapterTableRow()
{
    QModelIndex index = chapterTableView->selectionModel()->currentIndex();
    table->RemoveRow(index);
}

void GVNEditor::MoveChapterTableRowUp()
{
    QModelIndex sourceIndex = chapterTableView->selectionModel()->currentIndex();

    //Only move up if we have room
    if(!sourceIndex.row() - 1 < 0)
    {
        QModelIndex targetIndex = chapterTableView->model()->index(sourceIndex.row() - 1, sourceIndex.column()); //Previous index
        table->SwapRowData(sourceIndex, targetIndex);
        chapterTableView->selectionModel()->setCurrentIndex(targetIndex, QItemSelectionModel::SelectCurrent);
    }
}

void GVNEditor::MoveChapterTableRowDown()
{
    int numofEntries = table->rowCount(QModelIndex());
    QModelIndex sourceIndex = chapterTableView->selectionModel()->currentIndex();

    //Only move down if we have room
    if(sourceIndex.row() + 1 < numofEntries)
    {
        QModelIndex targetIndex = chapterTableView->model()->index(sourceIndex.row() + 1, sourceIndex.column()); //Previous index
        table->SwapRowData(sourceIndex, targetIndex);
        chapterTableView->selectionModel()->setCurrentIndex(targetIndex, QItemSelectionModel::SelectCurrent);
    }
}

void GVNEditor::LoadStoryData()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Story Data File"), QDir::currentPath(), tr("XML Files (*.xml)"));
    if(filePath != "")
    {
        qDebug() << "Chosen File: ";
        qDebug() << filePath;
        QFile newFile(filePath);
        table->LoadTableData(newFile);

        emit table->dataChanged(QModelIndex(), QModelIndex());
    }

}

void GVNEditor::SaveStoryDataAs()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Where to Save the Story Data File"), QDir::currentPath(), tr("XML Files (*.xml)"));
    if(filePath != "")
    {
        qDebug() << "Chosen File: ";
        qDebug() << filePath;
        QFile saveFile(filePath);
        table->SaveStoryData(saveFile);
    }
}
