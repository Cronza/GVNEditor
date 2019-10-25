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

#include "ChapterTableItem.h"
#include "ChapterTable.h"

///Constructor
ChapterTable::ChapterTable(const QStringList &headers, const QString &data, QObject *parent)
    : QAbstractItemModel(parent)
{
    //For each header, add it to the root data list
    QVector<QVariant> rootData;
    foreach (QString header, headers)
        rootData << header;

    //Create the "header "bar" of the table
    rootItem = new ChapterTableItem(rootData);
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
    ChapterTableItem *item = getItem(index);

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
ChapterTableItem *ChapterTable::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        ChapterTableItem *item = static_cast<ChapterTableItem*>(index.internalPointer());
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
    ChapterTableItem *parentItem = getItem(parent);

    //Get the child of this item
    ChapterTableItem *childItem = parentItem->child(row);

    //If a child
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

///Requests that the selected item create a row either as a child, or a succeeding element
bool ChapterTable::insertRows(int position, int rows, const QModelIndex &parent)
{
    ChapterTableItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildRow(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

//! [7]
QModelIndex ChapterTable::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    ChapterTableItem *childItem = getItem(index);
    ChapterTableItem *parentItem = childItem->parent();

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
    ChapterTableItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildRow(position, rows);
    endRemoveRows();

    return success;
}

//! [8]
int ChapterTable::rowCount(const QModelIndex &parent) const
{
    ChapterTableItem *parentItem = getItem(parent);

    return parentItem->childCount();
}
//! [8]

bool ChapterTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    ChapterTableItem *item = getItem(index);
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
void ChapterTable::setupModelData(const QStringList &lines, ChapterTableItem *parent)
{
    QList<ChapterTableItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].at(position) != ' ')
                break;
            ++position;
        }

        QString lineData = lines[number].mid(position).trimmed();

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
            ChapterTableItem *parent = parents.last();
            parent->insertChildRow(parent->childCount(), 1, rootItem->columnCount());
            for (int column = 0; column < columnData.size(); ++column)
                parent->child(parent->childCount() - 1)->setData(column, columnData[column]);
        }

        ++number;
    }
}
