#include "extendedjsonmodel.h"

//TODO : debug instanceChange() / not working on certain conditions

ExtendedJsonModel::ExtendedJsonModel(QString Root, QString Group, QString Instance, QString Item, QString Option, QStringList GroupParent, QStringList InstanceParent, QStringList ItemParent, QStringList OptionParent, QObject *parent) :
    QJsonModel(parent)
{
    RootType = Root;
    ItemType = Item;
    OptionType = Option;
    GroupType = Group;
    InstanceType = Instance;

    ItemParentType = ItemParent;
    OptionParentType = OptionParent;
    GroupParentType = GroupParent;
    InstanceParentType = InstanceParent;

    connect(this, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(dataChanged(QModelIndex,QModelIndex)));
    //connect(this, SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)), this, SLOT()
}

ExtendedJsonModel::~ExtendedJsonModel()
{

}



QModelIndex ExtendedJsonModel::appendRoot(QString RootName)
{
    Q_UNUSED(RootName);
    return load(":/" + RootType + ".json", QModelIndex());
}

QModelIndex ExtendedJsonModel::removeRoot(QModelIndex index)
{
    QJsonTreeItem* Item = getItem(index);
    if (Item->itemType() != RootType)
        return QModelIndex();

    QJsonTreeItem* ParentItem = getItem(index.parent());

    beginRemoveRows(index.parent(), index.row(), index.row());
    ParentItem->removeChildren(index.row(), 1);
    endRemoveRows();
    return index.parent();
}

QModelIndex ExtendedJsonModel::appendItem(QModelIndex parent, QString name)
{
    Q_UNUSED(name);
    QJsonTreeItem* ParentItem = getItem(parent);
    if (!ItemParentType.contains(ParentItem->itemType()))
        return QModelIndex();
    return load(":/" + ItemType + ".json", parent);

}

QModelIndex ExtendedJsonModel::removeItem(QModelIndex index)
{
    QJsonTreeItem* indexItem = getItem(index);
    QJsonTreeItem* parentItem = getItem(index.parent());
    if (indexItem->itemType() == ItemType) {
        beginRemoveRows(index.parent(), index.row(), index.row());
        parentItem->removeChildren(index.row(), 1);
        endRemoveRows();
        return index.parent();
    }
    else if (parentItem->itemType() == OptionType)
    {
        return this->removeItem(index.parent());
    }
    if (index.parent() == QModelIndex())
    {
        return QModelIndex();
    }
    return QModelIndex();
}

QModelIndex ExtendedJsonModel::appendGroup(QModelIndex parent)
{
    QJsonTreeItem* parentItem = getItem(parent);
    if (!GroupParentType.contains(parentItem->itemType()))
        return appendGroup(parent.parent());
    if (parent == QModelIndex())
        return QModelIndex();
    return load(":/" + GroupType + ".json", parent);
}

QModelIndex ExtendedJsonModel::removeGroup(QModelIndex index)
{
    QJsonTreeItem* Item = getItem(index);
    QJsonTreeItem* ParentItem = getItem(index.parent());
    if (Item->itemType() != GroupType)
        return QModelIndex();
    beginRemoveRows(index.parent(), index.row(), index.row());
    ParentItem->removeChildren(index.row(), 1);
    endRemoveRows();
    return index.parent();
}

QModelIndex ExtendedJsonModel::appendInstance(QModelIndex parent, QModelIndex Group, int instances)
{
    //Check Allowed InstanceParent Type
    QJsonTreeItem* parentItem = getItem(parent);
    if (!InstanceParentType.contains(parentItem->itemType()))
        return QModelIndex();


    QJsonTreeItem* groupItem = getItem(Group);

    QString groupName = groupItem->key();

    QJsonArray instanceArray = QJsonArray();

    QJsonValue groupValue = QJsonTreeItem::save2(groupItem);
    QJsonObject arrayObject = QJsonObject();

    for(int i = 0; i < instances; i++)
    {
        instanceArray.append(groupValue);
    }

    arrayObject.insert(groupName,instanceArray);

    QJsonDocument* ArrayDocument = new QJsonDocument(arrayObject);

    QModelIndex ItemIndex = loadJson(ArrayDocument->toJson(), parent);

    QJsonTreeItem* Item = getItem(ItemIndex);
    for(int i = 0; i < Item->childCount(); i++)
    {
        Item->child(i)->setItemType(InstanceType);
    }
    lockInstance(ItemIndex);

    QList<QPersistentModelIndex> groupInstances = groupItem->getInstancesIndex();
    groupInstances.append(QPersistentModelIndex(ItemIndex));
    groupItem->setInstancesIndex(groupInstances);

    return ItemIndex;
}

QModelIndex ExtendedJsonModel::removeInstance(QModelIndex Instance)
{
    if (Instance == QModelIndex())
    {
        return QModelIndex();
    }
    QJsonTreeItem* item = getItem(Instance);
    if (item->itemType() != InstanceType)
    {
        return removeInstance(Instance.parent());
    }
    else
    {
        QModelIndex instanceAray   = Instance.parent();
        QModelIndex instanceParent = instanceAray.parent();

        beginRemoveRows(instanceParent, instanceAray.row(), instanceAray.row());
        getItem(instanceParent)->removeChildren(instanceAray.row(), 1);
        endRemoveRows();
        return instanceParent;
    }
}


QModelIndex ExtendedJsonModel::insertRow(QModelIndex parent, QJsonTreeItem* child)
{
    QJsonTreeItem* parentItem = getItem(parent);
    beginInsertRows(parent, 0, 1);
    parentItem->appendChild(child);
    endInsertRows();
    return parent;
}

QModelIndex ExtendedJsonModel::getRootSelection(QModelIndex index)
{
    if (index.parent() == QModelIndex())
    {
        return index;
    }
    else
    {
        return getRootSelection(index.parent());
    }
}

void ExtendedJsonModel::lockInstance(QModelIndex index)
{
    QJsonTreeItem* item = getItem(index);
    item->setKeyLock(true);

    int i = 0;
    QModelIndex child = index.child(i, 0);
    while (child.isValid())
    {
        lockInstance(child);
        i++;
        child = index.child(i, 0);
    }
}

void ExtendedJsonModel::dataChanged(QModelIndex topLeft, QModelIndex bottomRight)
{
    if (topLeft == bottomRight)
    {
        instanceChange(topLeft, topLeft);
    }
}

void ExtendedJsonModel::instanceChange(QModelIndex source, QModelIndex group, QStringList path)
{
    if (group == QModelIndex())
        return;

    QJsonTreeItem* Item = getItem(group);
    if (Item->itemType() != GroupType)   //Parse Modified Value to get Path
    {
        qDebug() << Item->key();
        path.insert(0, data(group, Qt::DisplayRole).toString());
        instanceChange(source, group.parent(), path);
    }
    else //Parse Instances Index to modify value
    {
        if (path.size())
            path.takeLast();

        qDebug() << data(group, Qt::DisplayRole);

        QList<QPersistentModelIndex> instanceList = Item->getInstancesIndex();

        //Foreach Instance Index
        foreach (QPersistentModelIndex instance, instanceList) {

            if (path.size())
            {
                //Foreach Instances Array
                int i = 0;
                QModelIndex child = instance.child(i, 0);
                while(child.isValid())
                {
                    //Foreach Path Elements
                    QModelIndex target = child;
                    foreach (QString pathIndex, path) {
                        //Find Tree Child for String Path
                        int c = 0;
                        QModelIndex pathChild = target.child(c, 0);
                        QString pathChildKey = data(pathChild, Qt::DisplayRole).toString();

                        while(pathChild.isValid() && pathChildKey != pathIndex)
                        {
                            c++;
                            pathChild = target.child(c, 0);
                            pathChildKey = data(pathChild, Qt::DisplayRole).toString();
                        }
                        //target = target.child(pathIndex.row(), pathIndex.column());
                        target = pathChild;
                        qDebug() << data(target, Qt::DisplayRole);
                    }
                    i++;
                    child = instance.child(i, 0);

                    if (target.isValid())
                    {
                        target = index(source.row(), source.column(), target);
                        setData(target, data(source, Qt::DisplayRole));
                        blockSignals(true); //prevent to sent signals for each array elements

                    }
                }
                blockSignals(false);
            }
            else
            {
                setData(instance, data(source, Qt::DisplayRole));
            }
        }
    }
}

QStringList ExtendedJsonModel::getInstancePath(QModelIndex source, QModelIndex group, QStringList path)
{
    if (group == QModelIndex())
        return path;

    QJsonTreeItem* Item = getItem(group);
    if (Item->itemType() != GroupType)   //Parse Modified Value to get Path
    {
        qDebug() << Item->key();
        path.insert(0, data(group, Qt::DisplayRole).toString());
        instanceChange(source, group.parent(), path);
    }
    return path;
//    while ()
}
