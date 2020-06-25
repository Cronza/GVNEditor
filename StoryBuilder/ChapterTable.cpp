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
ChapterTable::ChapterTable(const QStringList &headers, const QString &data)
    : QAbstractItemModel()
{
    //For each header, add it to the root data list
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    //Create the "header "bar" of the table
    rootItem = new DialogueItem(rootData);

    //Setup each of the table items
    qDebug() << data;
    setupModelData(data.split(QString("\n")), rootItem);
}

///Destructor
ChapterTable::~ChapterTable()
{
    delete rootItem;
}

///A union representing the data of the table
QVariant ChapterTable::data(const QModelIndex &index, int role) const
{
    //If the index is valid, return a QVariant instance
    if (!index.isValid())
        return QVariant();

    //If the correct role is assigned, return a QVariant instance
    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    //Create a table item
    DialogueItem *item = getItem(index);

    //Return the data from the generated item object
    return item->data(index.column());
}

///Use the Qt flag system to define properties of the table
Qt::ItemFlags ChapterTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

///If the provided index is valid, return a pointer to the item associated with that index
DialogueItem *ChapterTable::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        DialogueItem *item = static_cast<DialogueItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

///Returns the
QVariant ChapterTable::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

//Retrieve an object representing the slot information for the given table position
QModelIndex ChapterTable::index(int row, int column, const QModelIndex &parent) const
{
    //Unsure what this does...................................
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    //Get the parent of this item
    DialogueItem *parentItem = getItem(parent);

    //Get the child of this item
    DialogueItem *childItem = parentItem->child(row);

    //If a child
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

///Requests that the selected item create a row either as a child, or a succeeding element
bool ChapterTable::insertRows(int position, int rows, const QModelIndex &parent)
{
    DialogueItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildRow(position, rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex ChapterTable::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DialogueItem *childItem = getItem(index);
    DialogueItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

///Returns the number of columns in the table
int ChapterTable::columnCount(const QModelIndex & /* parent */) const
{
    return rootItem->columnCount();
}
bool ChapterTable::removeRows(int position, int rows, const QModelIndex &parent)
{
    DialogueItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildRow(position, rows);
    endRemoveRows();

    return success;
}

//! [8]
int ChapterTable::rowCount(const QModelIndex &parent) const
{
    DialogueItem *parentItem = getItem(parent);

    return parentItem->childCount();
}
//! [8]

bool ChapterTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    DialogueItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool ChapterTable::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

///Configure the table data
void ChapterTable::setupModelData(const QStringList &lines, DialogueItem *root)
{   
    //Load the default xml data, and read the contents in
    QDomDocument xmlDoc;
    QFile xmlFile("C:/Users/garre/Desktop/Scripts/GVNEditor/Example_Story_Data.xml");
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



        //parent->insertChildRow(parent->childCount(), 1, rootItem->columnCount());
        //Set the top level details for each column

        //Create a row, then assign information to each column for that row
        DialogueItem* newItem = root->insertChildRow(root->childCount(),  rootItem->columnCount());
        newItem->setData(0, speaker);
        newItem->setData(1, dialogue);
        DialogueItem* settingItem = newItem->insertChildRow(0, rootItem->columnCount());
        settingItem->setData(0, "Test: ");

        //root->insertChildRow(root->childCount(), rootItem->columnCount());





    }


    //while (number < lines.count()) {

    //for(int i = 0; i < lines.count(); i++)
    //{
    //    int position = 0;
        //while (position < lines[number].length()) {
        //    if (lines[number].at(position) != ' ')
        //        break;
        //    ++position;
        //}

    //    QString lineData = lines[i];
        //.mid(position).trimmed();
        //qDebug() << qPrintable(lineData);
    //}
                        /*
        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QVector<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            DialogueItem *parent = parents.last();
            parent->insertChildRow(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        }

        ++number;
    }
            */
}
