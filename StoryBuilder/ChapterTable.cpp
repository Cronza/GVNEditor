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

#include <QtWidgets>
#include <QtXml>
#include <QFile>
#include "ChapterTable.h"

///Constructor
ChapterTable::ChapterTable(QObject *parent)
    : QAbstractTableModel(parent)
{

}
ChapterTable::~ChapterTable()
{

}

/* ----- INHERITED FUNCTIONS ----- */
Qt::ItemFlags ChapterTable::flags(const QModelIndex &index) const
{
    Q_UNUSED(index);

    /*
    We don't care about the specifics of any given item,
    so by default they're always editable, and selectable
    */
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QVariant ChapterTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::EditRole && role != Qt::DisplayRole)
        return QVariant();

    return tableData[index.column()][index.row()];
}

QVariant ChapterTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return tr("%1").arg(columnNames[section]); //Tr only accepts string literals, so we need to bypass that
    }
    if (role == Qt::DisplayRole && orientation == Qt::Vertical) {
        return tr("%1").arg(section);
    }
    return QVariant();
}

int ChapterTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return tableData.length();
}

int ChapterTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return tableData[0].length(); //Use index 0 as an example. Any row would work

}

bool ChapterTable::setData(const QModelIndex &index, const QVariant &newData, int role)
{
    if(!index.isValid() || role != Qt::EditRole)
        return false;

    tableData[index.column()][index.row()] = newData.toString();

    emit dataChanged(index, index);
    return true;
}

/* ----- CUSTOM FUNCTIONS ----- */

void ChapterTable::InitializeTableData(QFile &file)
{
    //Initialize a list for each column in the table
    for(int i = 0; i < columnNames.length(); i++)
    {
        tableData.append(QList<QVariant>());
    }

    //Load some default text
    LoadTableData(file);
}

void ChapterTable::AddRow(QModelIndex &index)
{
    int row = index.row();

    //Inform the model to update view changes
    beginInsertRows(QModelIndex(), row, row);

    for(int i = 0; i < tableData.length(); i++){
        tableData[i].insert(row, "");
    }

    //Inform the view that we're done
    endInsertRows();
}

void ChapterTable::RemoveRow(QModelIndex &index)
{
    int row = index.row();

    //Inform the model to update view changes
    beginRemoveRows(QModelIndex(), row, row);

    for(int i = 0; i < tableData.length(); i++){
        tableData[i].removeAt(row);
    }

    //Inform the view that we're done
    endRemoveRows();

}

void ChapterTable::SwapRowData(QModelIndex &sourceIndex, QModelIndex &targetIndex)
{
    //Swap data with the row above this entry
    QList<QVariant> temp;
    int sourceRow = sourceIndex.row();
    int targetRow = targetIndex.row();

    //Cache the source index data
    for(int i = 0; i < tableData.length(); i++){
        temp.append(tableData[i][sourceRow]);
    }

    //Copy the target index data to the source index
    for(int i = 0; i < tableData.length(); i++){
        tableData[i][sourceRow] = tableData[i][targetRow];
    }

    //Update the target index data with the cached source index data
    for(int i = 0; i < tableData.length(); i++){
        tableData[i][targetRow] = temp[i];
    }

    emit dataChanged(sourceIndex, targetIndex);
}

void ChapterTable::LoadTableData(QFile &storyFile)
{   
    //Halt table reading so we can clear data
    beginResetModel();

    //Clear our table data in case there's existing table data
    for(int i = 0; i < tableData.length(); i++){
        tableData[i].clear();
    }

    //Load the default xml data, and read the contents in
    QDomDocument xmlDoc;
    QFile &xmlFile = storyFile;
    xmlFile.open(QFile::ReadOnly);
    xmlDoc.setContent(xmlFile.readAll());
    xmlFile.close();

    //Extract the chapter text section
    //QDomElement xmlRoot = xmlDoc.documentElement();
    QDomNodeList dialogueLines = xmlDoc.elementsByTagName("ChapterText").item(0).childNodes();

    //Add entries for each dialogue entry in the xml
    for(int i = 0; i < dialogueLines.count(); i++)
    {
        //Get each dialogue node, then grab each setting, then grab the text element of that setting
        QDomNodeList dialogueDetails = dialogueLines.item(i).childNodes();

        QString speaker = dialogueDetails.item(0).firstChild().nodeValue();
        QString dialogue = dialogueDetails.item(1).firstChild().nodeValue();
        QString sprite = dialogueDetails.item(2).firstChild().nodeValue();
        qDebug() << speaker;
        qDebug() << dialogue;
        qDebug() << sprite;

        //Create a row, then assign information to each column for that row
        //DialogueItem* newItem = rootItem->AddChildRow(rootItem->GetNumOfChildren(),  rootItem->GetNumOfColumns());
        //newItem->SetData(0, speaker);
        //newItem->SetData(1, dialogue);
        tableData[0].append(speaker);
        tableData[1].append(dialogue);

        /*
        DialogueItem* settingItem = newItem->AddChildRow(0, rootItem->GetNumOfColumns());
        settingItem->SetData(0, "Sprite:");
        settingItem->SetData(1, sprite);
        settingItem = newItem->AddChildRow(1, rootItem->GetNumOfColumns());
        settingItem->SetData(0, "Position:");
        settingItem->SetData(1, "None");
        */

    }

    //Rebuild the table
    endResetModel();
}

void ChapterTable::SaveStoryData(QFile &saveFile)
{
    /*
        We'll be using an empty template file to save out our table information, as the
        XML schema for the engine is in C#, and rebuilding it here would cause
        duplication issues
    */

    QDomDocument xmlDoc;
    QFile templateXMLFile(":/templates/Story_Data_Template.xml");

    templateXMLFile.open(QFile::ReadOnly);
    xmlDoc.setContent(templateXMLFile.readAll());
    templateXMLFile.close();

    QDomNode entriesContainer = xmlDoc.elementsByTagName("ChapterText").item(0);

    for(int x = 0; x < rowCount(QModelIndex()); x++)
    {
        QDomNode entry = xmlDoc.createElement("Item");

        for(int y = 0; y < columnCount(QModelIndex()); y++)
        {
            QDomNode entryDetail = xmlDoc.createElement("Item");
            QDomNode entryDetailText = xmlDoc.createTextNode(tableData[y][x].toString());
            entryDetail.appendChild(entryDetailText);
            entry.appendChild(entryDetail);
        }

        entriesContainer.appendChild(entry);
    }

    saveFile.open(QFile::ReadWrite);


    //Use a text stream object to bypass char* param requirement
    QTextStream stream(&saveFile);
    stream << xmlDoc.toString();
    saveFile.close();
}

