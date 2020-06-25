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

#ifndef ChapterTable_H
#define ChapterTable_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "DialogueItem.h"

class ChapterTable : public QAbstractItemModel
{
    Q_OBJECT

public:
    ///Constructor
    ChapterTable(const QStringList &headers, const QString &data);

    ///Deconstructor
    ~ChapterTable() override;

    ///Held data
    QVariant data(const QModelIndex &index, int role) const override;

    ///Table header
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    ///A trackable index value
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;

    ///The parent item of an item
    QModelIndex parent(const QModelIndex &index) const override;

    ///How many rows exist in the table
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    ///How many columns exist in the table
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    ///Use the Qt flag system to define the properties of the table
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    ///Set the data of a particuler index
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    ///Set the header data of the table
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;

    ///Insert a row into the table
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;

    ///Remove a row from the table
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;

private:
    ///Initial setup function for the table data
    void setupModelData(const QStringList &lines, DialogueItem *parent);

    ///Retrieve an element from the table
    DialogueItem *getItem(const QModelIndex &index) const;

    ///The root item for the table
    DialogueItem *rootItem;
};
//! [2]

#endif // ChapterTable_H
