#ifndef QJSONMODEL_H
#define QJSONMODEL_H

#include <QAbstractItemModel>
#include "qjsonitem.h"
#include <QModelIndex>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIcon>

namespace UserRole {
    typedef enum {
        JsonType = Qt::UserRole + 1,
        ItemType = Qt::UserRole + 2,
        KeyLock = Qt::UserRole + 10,
        ValueLock = Qt::UserRole + 11
    } UserRole;
}


typedef bool (*JsonFlag)(QString);

class QJsonModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit QJsonModel(QObject *parent = 0);
    ~QJsonModel();
    QModelIndex load(const QString& fileName, QModelIndex parent = QModelIndex());
    QModelIndex load(QIODevice * device, QModelIndex parentItem = QModelIndex());
    QModelIndex loadJson(const QByteArray& json, QModelIndex parent = QModelIndex());
    bool save(const QString& filename, QModelIndex root = QModelIndex());
    bool save(QIODevice * device, QModelIndex root = QModelIndex());

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    void setIcon(const QJsonValue::Type& type, const QIcon& icon);

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) Q_DECL_OVERRIDE;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    QString getItemType(const QModelIndex index);
    virtual QJsonTreeItem *getItem(const QModelIndex &index) const;

protected:
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    QJsonTreeItem *rootItem() const;
    void setRootItem(QJsonTreeItem *rootItem);
    QJsonDocument document() const;
    void setDocument(const QJsonDocument &document);

private:
    QJsonTreeItem * mRootItem;
    bool mRootItemSet;
    QJsonDocument mDocument;
    QStringList mHeaders;
    QHash<QJsonValue::Type, QIcon> mTypeIcons;


};

#endif // QJSONMODEL_H
