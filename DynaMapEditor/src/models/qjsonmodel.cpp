/***********************************************
    Copyright (C) 2014  Schutz Sacha
    This file is part of QJsonModel (https://github.com/dridk/QJsonmodel).

    QJsonModel is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QJsonModel is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QJsonModel.  If not, see <http://www.gnu.org/licenses/>.

**********************************************/

#include "qjsonmodel.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIcon>
#include <QFont>
#include <QMessageBox>

QJsonModel::QJsonModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    mRootItem = new QJsonTreeItem();
    mRootItem->setKey("root");
    mHeaders.append("key");
    mHeaders.append("value");
    mRootItemSet = false;
}

QJsonModel::~QJsonModel()
{
    delete mRootItem;
}

QModelIndex QJsonModel::load(const QString &fileName, QModelIndex parent)
{
    QFile file(fileName);
    QModelIndex success = QModelIndex();
    if (file.open(QIODevice::ReadOnly)) {
        success = load(&file, parent);
        file.close();
    }
    return success;
}

QModelIndex  QJsonModel::load(QIODevice *device, QModelIndex parentItem)
{
    return loadJson(device->readAll(), parentItem);
}

QModelIndex QJsonModel::loadJson(const QByteArray &json, QModelIndex parentIndex)
{
    mDocument = QJsonDocument::fromJson(json);
    if (!mDocument.isNull())
    {
        QJsonTreeItem* parentItem = getItem(parentIndex);
        if (mRootItemSet)
        {
            beginInsertRows(parentIndex, parentItem->childCount(), parentItem->childCount());
            QJsonTreeItem::load(QJsonValue(mDocument.object()).toObject(), parentItem, true);
            endInsertRows();
        }
        else
        {
            beginResetModel();
            mRootItem = QJsonTreeItem::load(QJsonValue(mDocument.object()).toObject(), parentItem);
            mRootItemSet = true;
            endResetModel();
        }
        QModelIndex itemIndex = index(parentItem->childCount() - 1, 0, parentIndex);
        return itemIndex;
    }
    return QModelIndex();
}

bool QJsonModel::save(const QString &filename, QModelIndex root)
{
    QFile file(filename);
    bool success = false;
    if (file.open(QIODevice::WriteOnly)) {
        success = save(&file, root);
        file.close();
    }
    else success = false;

    return success;
}

bool QJsonModel::save(QIODevice *device, QModelIndex root)
{
    bool success = false;
    QJsonTreeItem* rootItem = getItem(root);
    QJsonDocument *SaveJson = new QJsonDocument(QJsonTreeItem::save2(rootItem).toObject());

    if (!SaveJson->isNull())
        device->write(SaveJson->toJson(QJsonDocument::Indented));
        success = true;
    return success;
}


QVariant QJsonModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();


    QJsonTreeItem *item = static_cast<QJsonTreeItem*>(index.internalPointer());


//    if ((role == Qt::DecorationRole) && (index.column() == 0)){

//        return mTypeIcons.value(item->jsonType());
//    }


//    if (role == Qt::DisplayRole || role == Qt::EditRole) {

//        if (index.column() == 0)
//            return QString("%1").arg(item->key());

//        if (index.column() == 1)
//            return QString("%1").arg(item->value());
//    }

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        if (index.column() == 0)
            return item->key();
        if (index.column() == 1)
            return item->value();
        break;
    case UserRole::JsonType:
        return item->jsonType();
        break;
    case UserRole::ItemType:
        return item->itemType();
        break;
    case UserRole::KeyLock:
        return item->keyLock();
        break;
    case UserRole::ValueLock:
    default:
        break;
    }

    return QVariant();

}

QVariant QJsonModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {

        return mHeaders.value(section);
    }
    else
        return QVariant();
}

QModelIndex QJsonModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    QJsonTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<QJsonTreeItem*>(parent.internalPointer());

    QJsonTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex QJsonModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    QJsonTreeItem *childItem = static_cast<QJsonTreeItem*>(index.internalPointer());
    QJsonTreeItem *parentItem = childItem->parent();

    if (parentItem == mRootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int QJsonModel::rowCount(const QModelIndex &parent) const
{
    QJsonTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = mRootItem;
    else
        parentItem = static_cast<QJsonTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int QJsonModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

void QJsonModel::setIcon(const QJsonValue::Type &type, const QIcon &icon)
{
    mTypeIcons.insert(type,icon);
}

Qt::ItemFlags QJsonModel::flags(const QModelIndex &index) const

{
    if (!index.isValid())
        return 0;

    return getItem(index)->flags(index);
}

bool QJsonModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    QJsonTreeItem *item = getItem(index);
    if (index.column() == 0)
    {
//        if (item->keyLock())
//            return false;
        item->setKey(value.toString());
    }
    else
    {
        if (item->valueLock())
            return false;
        item->setValue(value.toString());
    }
    bool result = true;
    if (result)
        emit dataChanged(index, index);

    return result;
}

bool QJsonModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    mHeaders[section] = value.toString();
    bool result = true;
    if (result)
        emit headerDataChanged(orientation, section, section);
    return result;
}

QString QJsonModel::getItemType(const QModelIndex index)
{
    return getItem(index)->itemType();
}

bool QJsonModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(position);
    QJsonTreeItem *parentItem = getItem(parent);
    bool success = true;

    beginInsertRows(parent, parentItem->childCount(), parentItem->childCount() + rows - 1);
    for(int i = 0; i < rows; i++)
    {
        parentItem->appendChild(new QJsonTreeItem(parentItem));
    }
    endInsertRows();

    return success;
}

bool QJsonModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    QJsonTreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

QJsonTreeItem *QJsonModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        QJsonTreeItem *item = static_cast<QJsonTreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem();
    //return getItem(QModelIndex());
}
QJsonTreeItem *QJsonModel::rootItem() const
{
    return mRootItem;
}

void QJsonModel::setRootItem(QJsonTreeItem *rootItem)
{
    mRootItem = rootItem;
}
QJsonDocument QJsonModel::document() const
{
    return mDocument;
}

void QJsonModel::setDocument(const QJsonDocument &document)
{
    mDocument = document;
}



