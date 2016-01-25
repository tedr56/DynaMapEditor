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
#include "qjsonitem.h"

QJsonTreeItem::QJsonTreeItem(QJsonTreeItem *parent, QString name, bool keyLock, QString Value, bool valueLock)
{
    mParent = parent;
    setJsonType(QJsonValue::Object);
    setKey(name);
    if (Value.size())
        setValue(Value);
    setKeyLock(keyLock);
    setValueLock(valueLock);

    mItem = "Value";
}

QJsonTreeItem::~QJsonTreeItem()
{
    qDeleteAll(mChilds);

}

void QJsonTreeItem::appendChild(QJsonTreeItem *item)
{
    setValue("");
    mChilds.append(item);
}

QJsonTreeItem *QJsonTreeItem::child(int row)
{
    return mChilds.value(row);
}

QJsonTreeItem *QJsonTreeItem::parent()
{
    return mParent;
}

int QJsonTreeItem::childCount() const
{
    return mChilds.count();
}

int QJsonTreeItem::row() const
{
    if (mParent)
        return mParent->mChilds.indexOf(const_cast<QJsonTreeItem*>(this));

    return 0;
}

int QJsonTreeItem::column() const
{
    return childCount();
}

void QJsonTreeItem::setKey(const QString &key)
{
    mKey = key;
}

bool QJsonTreeItem::setValue(const QString &value)
{
    mValue = value;
    return true;
}

void QJsonTreeItem::setJsonType(const QJsonValue::Type &type)
{
    mType = type;
}

QString QJsonTreeItem::key() const
{
    return mKey;
}

QString QJsonTreeItem::value() const
{
    return mValue;
}

QJsonValue::Type QJsonTreeItem::jsonType() const
{
    return mType;
}

bool QJsonTreeItem::removeChildren(int position, int rows)
{
    if (position < 0 || position + rows > mChilds.size())
        return false;

    for (int row = 0; row < rows; ++row)
        delete mChilds.takeAt(position);

    return true;
}

QJsonTreeItem *QJsonTreeItem::load(const QJsonValue& value, QJsonTreeItem* parentItem, bool ignoreRoot)
{
    QJsonTreeItem * rootItem;
    if (ignoreRoot)
    {
        rootItem = parentItem;
    }
    else
    {
        rootItem = new QJsonTreeItem(parentItem);
        rootItem->setKey("root");
    }


    if ( value.isObject())
    {
        foreach (QString key , value.toObject().keys()){
            if (key == "Item")
            {
                rootItem->setItemType(value.toObject().value(key).toVariant().toString());
            }
            else if (key == "Lock")
            {
                QString Lock = value.toObject().value(key).toVariant().toString();
                if (Lock == "key")
                {
                    rootItem->setKeyLock(true);
                }
                else if (Lock == "value")
                {
                    rootItem->setValueLock(true);
                }

            }
            else
            {
                rootItem->setJsonType(QJsonValue::Object);
                QJsonValue v = value.toObject().value(key);
                QJsonTreeItem * child = load(v,rootItem);
                if (child)
                {
                    child->setKey(key);
                    child->setJsonType(v.type());
                    rootItem->appendChild(child);
                }
            }
        }
    }
    else if ( value.isArray())
    {
        //Get all QJsonValue childs
        int index = 0;
        foreach (QJsonValue v , value.toArray()){

            rootItem->setJsonType(QJsonValue::Array);
            QJsonTreeItem * child = load(v,rootItem);
            child->setKey(QString::number(index));
            child->setJsonType(v.type());
            rootItem->appendChild(child);
            ++index;
        }
    }
    else
    {
        rootItem->setValue(value.toVariant().toString());
        rootItem->setJsonType(value.type());
        rootItem->setKeyLock(true);
    }

    return rootItem;
}

QJsonValue *QJsonTreeItem::save(QJsonTreeItem *root)
{
    QJsonValue* value = new QJsonValue();

    if (root->jsonType() == QJsonValue::Object)
    {
        if (root->childCount())     //Root Value is Object
        {
            QJsonObject ChildObjects = QJsonObject();
            for (int children = 0; children < root->childCount(); children++)
            {
                QJsonTreeItem* ChildItem  = root->child(children);
                QJsonValue* ChildValue = QJsonTreeItem::save(ChildItem);
                QString    ChildKey   = ChildItem->key();
                ChildObjects.insert(ChildKey, *ChildValue);
            }
            if (root->itemType().size())
                ChildObjects.insert("Item", QJsonValue(root->itemType()));
            if (root->keyLock())
                ChildObjects.insert("Lock", QJsonValue("key"));
            if (root->valueLock())
                ChildObjects.insert("Lock", QJsonValue("value"));
            value = new QJsonValue(ChildObjects);
        }
        else                        //Root Value is Root.Value
        {
            value = new QJsonValue(root->value());
        }
    }
    else if (root->jsonType() == QJsonValue::Array)
    {
        QJsonArray ChildObjects = QJsonArray();
        for (int children = 0; children < root->childCount(); children++)
        {
            QJsonTreeItem* ChildItem  = root->child(children);
            QJsonValue* ChildValue = QJsonTreeItem::save(ChildItem);
            QString    ChildKey   = ChildItem->key();
            ChildObjects.append(*ChildValue);
        }
        value = new QJsonValue(ChildObjects);

    }
    else
    {
        value = new QJsonValue(root->value());
    }
    return value;
}

QJsonValue QJsonTreeItem::save2(QJsonTreeItem *root)
{
    QJsonValue value;

    if (root->jsonType() == QJsonValue::Object)
    {
        if (root->childCount())     //Root Value is Object
        {
            QJsonObject ChildObjects = QJsonObject();
            for (int children = 0; children < root->childCount(); children++)
            {
                QJsonTreeItem* ChildItem  = root->child(children);
                QJsonValue ChildValue = QJsonTreeItem::save2(ChildItem);
                QString    ChildKey   = ChildItem->key();
                ChildObjects.insert(ChildKey, ChildValue);
            }
            if (root->itemType().size())
                ChildObjects.insert("Item", QJsonValue(root->itemType()));
            if (root->keyLock())
                ChildObjects.insert("Lock", QJsonValue("key"));
            if (root->valueLock())
                ChildObjects.insert("Lock", QJsonValue("value"));
            QJsonValue childValue(ChildObjects);
            value = childValue;
        }
        else                        //Root Value is Root.Value
        {
            QJsonValue rootValue(root->value());
            value = rootValue;
        }
    }
    else if (root->jsonType() == QJsonValue::Array)
    {
        QJsonArray ChildObjects = QJsonArray();
        for (int children = 0; children < root->childCount(); children++)
        {
            QJsonTreeItem* ChildItem  = root->child(children);
            QJsonValue ChildValue = QJsonTreeItem::save2(ChildItem);
            QString    ChildKey   = ChildItem->key();
            ChildObjects.append(ChildValue);
        }
        QJsonValue childValue(ChildObjects);
        value = childValue;

    }
    else
    {
        QJsonValue rootValue(root->value());
        value = rootValue;
    }
    return value;
}

bool QJsonTreeItem::keyLock() const
{
    return mKeyLock;
}

void QJsonTreeItem::setKeyLock(bool keyLock)
{
    mKeyLock = keyLock;
}

Qt::ItemFlags QJsonTreeItem::flags(const QModelIndex &index)
{
    if (keyLock() && index.column() == 0)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    if (valueLock() && index.column() == 1)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    if (childCount() && index.column() == 1)
    {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool QJsonTreeItem::valueLock() const
{
    return mValueLock;
}

void QJsonTreeItem::setValueLock(bool valueLock)
{
    mValueLock = valueLock;
}
QString QJsonTreeItem::itemType() const
{
    return mItemType;
}

void QJsonTreeItem::setItemType(const QString &itemType)
{
    mItemType = itemType;
}
QList<QJsonTreeItem *> QJsonTreeItem::getInstances() const
{
    return instances;
}

void QJsonTreeItem::setInstances(const QList<QJsonTreeItem *> &value)
{
    instances = value;
}
QList<QPersistentModelIndex> QJsonTreeItem::getInstancesIndex() const
{
    return instancesIndex;
}

void QJsonTreeItem::setInstancesIndex(const QList<QPersistentModelIndex> &value)
{
    instancesIndex = value;
}






