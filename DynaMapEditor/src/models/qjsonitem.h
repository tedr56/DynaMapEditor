#ifndef JSONITEM_H
#define JSONITEM_H
#include <QtCore>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>


//TODO : delete QList<QJsonTreeItem*> instances   or    QList<QPersistentModelIndex> instancesIndex;

class QJsonTreeItem
{
public:
    QJsonTreeItem(QJsonTreeItem * parent = 0, QString name = "", bool keyLock = false, QString Value = "", bool valueLock = false);
    virtual ~QJsonTreeItem();
    void appendChild(QJsonTreeItem * item);
    QJsonTreeItem *child(int row);
    QJsonTreeItem *parent();
    int childCount() const;
    int row() const;
    int column() const;
    void setKey(const QString& key);
    bool setValue(const QString& value);
    void setJsonType(const QJsonValue::Type& jsonType);
    QString key() const;
    QString value() const;
    QJsonValue::Type jsonType() const;

    bool removeChildren(int position, int rows);

    static QJsonTreeItem* load(const QJsonValue& value, QJsonTreeItem * parentItem = 0, bool ignoreRoot= false);
    static QJsonValue* save(QJsonTreeItem*);
    static QJsonValue  save2(QJsonTreeItem*);

    bool keyLock() const;
    void setKeyLock(bool keyLock);

    Qt::ItemFlags flags(const QModelIndex &index);

    bool valueLock() const;
    void setValueLock(bool valueLock);

    QString itemType() const;
    void setItemType(const QString &itemType);


    QList<QJsonTreeItem *> getInstances() const;
    void setInstances(const QList<QJsonTreeItem *> &value);

    QList<QPersistentModelIndex> getInstancesIndex() const;
    void setInstancesIndex(const QList<QPersistentModelIndex> &value);

signals:
    void dataModify(QStringList, QString);

public slots:
    void dataModified(QStringList, QString);

private:
    QString mItemType;

    bool mKeyLock;
    bool mValueLock;
    QString mKey;
    QString mValue;
    QJsonValue::Type mType;
    QList<QJsonTreeItem*> mChilds;
    QJsonTreeItem * mParent;

    QString mItem;

    QList<QJsonTreeItem*> instances;
    QList<QPersistentModelIndex> instancesIndex;

};

#endif // JSONITEM_H
