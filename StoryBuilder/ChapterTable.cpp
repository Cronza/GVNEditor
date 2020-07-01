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
#include "DialogueItem.h"
#include "ChapterTable.h"

///Constructor
ChapterTable::ChapterTable(QObject *parent)
    : QAbstractTableModel(parent)
{
    /*
    qDebug() << "Chapter Table Constructor Function";
    //For each header, add it to the root data list
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    //Create the "header "bar" of the table
    rootItem = new DialogueItem(rootData);

    //UpdateTableData("D:\\Scripts\\build-GVNEditor-Desktop_Qt_5_12_0_MinGW_64_bit-Debug\\Example_Story_Data.xml");
    UpdateTableData("C:\\Users\\garre\\Desktop\\Scripts\\GVNEditor\\Example_Story_Data.xml");
    */
}

///Destructor
ChapterTable::~ChapterTable()
{
    //delete rootItem;
}


// Create a method to populate the model with data:
void ChapterTable::populateData(const QList<QString> &speakerName,const QList<QString> &dialogueLine)
{
    dataFields[0].clear();
    dataFields[0] = speakerName;
    dataFields[1].clear();
    dataFields[1] = dialogueLine;
    return;
}


Qt::ItemFlags ChapterTable::flags(const QModelIndex &index) const
{
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

    return dataFields[index.column()][index.row()];
}

QVariant ChapterTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return tr("%1").arg(columnNames[section]); //Tr only accepts string literals, so we need to bypass that

    }
    return QVariant();
}

int ChapterTable::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return dataFields.size();
}

int ChapterTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return dataFields[0].length(); //Use index 0 as an example. Any row would work

}

bool ChapterTable::insertRows(int position, int rows, const QModelIndex &index)
{
    return false;
    /*
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        rowData.insert(position, { QString(), QString() });

    endInsertRows();
    return true;
    */

    //qDebug() << "InsertRows Function";
    //DialogueItem *parentItem = getItem(parent);
    //bool success;

    //beginInsertRows(parent, position, position + rows - 1);
    //success = parentItem->AddChildRow(position, rootItem->GetNumOfColumns());
    //endInsertRows();

    //return success;
}

bool ChapterTable::removeRows(int position, int rows, const QModelIndex &index)
{
    return false;
    /*
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        rowData.removeAt(position);

    endRemoveRows();
    return true;
    */
    //qDebug() << "Remove Rows Function";
    //DialogueItem *parentItem = getItem(parent);
    //bool success = true;

    //beginRemoveRows(parent, position, position + rows - 1);
    //success = parentItem->RemoveChildRow(position, rows);
    //endRemoveRows();

    //return success;
}

bool ChapterTable::setData(const QModelIndex &index, const QVariant &newData, int role)
{
    if(!index.isValid() || role != Qt::EditRole)
        return false;

    dataFields[index.column()][index.row()] = newData.toString();
    return true;
}

void ChapterTable::UpdateTableData(QString storyFilePath)
{   

    qDebug() << "Update Table Data Function";
    //Load the default xml data, and read the contents in
    QDomDocument xmlDoc;
    QFile xmlFile(storyFilePath);
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
        dataFields[0].append(speaker);
        dataFields[1].append(dialogue);

        /*
        DialogueItem* settingItem = newItem->AddChildRow(0, rootItem->GetNumOfColumns());
        settingItem->SetData(0, "Sprite:");
        settingItem->SetData(1, sprite);
        settingItem = newItem->AddChildRow(1, rootItem->GetNumOfColumns());
        settingItem->SetData(0, "Position:");
        settingItem->SetData(1, "None");
        */

    }
}
