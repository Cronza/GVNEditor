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

/*
    DialogueItem.cpp

    A container for items of data supplied by the simple tree model.
*/

#include "DialogueItem.h"

#include <QStringList>

///Constructor
DialogueItem::DialogueItem(const QVector<QVariant> &data, DialogueItem *parent)
{
    parentItem = parent;
    itemData = data;
}


///Deconstructor
DialogueItem::~DialogueItem()
{
    qDeleteAll(childItems);
}


//! [2]
DialogueItem *DialogueItem::child(int number)
{
    return childItems.value(number);
}
//! [2]

//! [3]
int DialogueItem::childCount() const
{
    return childItems.count();
}
//! [3]

///Returns the number of children for this item
int DialogueItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<DialogueItem*>(this));

    return 0;
}

///Returns the data held by this item
QVariant DialogueItem::data(int column) const
{
    return itemData.value(column);
}

///Adds a row as a child to this item
DialogueItem* DialogueItem::insertChildRow(int position, int columns)
{
    QVector<QVariant> data(columns);
    DialogueItem *item = new DialogueItem(data, this);
    childItems.insert(position, item);

    return item;
}



//Return the number of columns in this item
int DialogueItem::columnCount() const
{
    return itemData.count();
}

//Returns the parent item of this item
DialogueItem *DialogueItem::parent()
{
    return parentItem;
}

//Removes the first child item of this item
bool DialogueItem::removeChildRow(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}

//! [11]
bool DialogueItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size())
        return false;

    itemData[column] = value;
    return true;
}
//! [11]
