#ifndef EXTENDEDJSONMODEL_H
#define EXTENDEDJSONMODEL_H

#include "qjsonmodel.h"

class ExtendedJsonModel : public QJsonModel
{
Q_OBJECT
public:
    explicit ExtendedJsonModel(QString Root,
                               QString Group,
                               QString Instance,
                               QString Item,
                               QString Option,
                               QStringList GroupParent,
                               QStringList InstanceParent,
                               QStringList ItemParent,
                               QStringList OptionParent,
                               QObject *parent = 0);
    ~ExtendedJsonModel();

    QModelIndex appendRoot(QString RootName = 0);
    QModelIndex removeRoot(QModelIndex index);
    QModelIndex appendItem(QModelIndex parent, QString name = "");
    QModelIndex removeItem(QModelIndex index);
    QModelIndex appendGroup(QModelIndex parent);
    QModelIndex removeGroup(QModelIndex index);
    QModelIndex appendInstance(QModelIndex parent, QModelIndex Group, int instances);
    QModelIndex removeInstance(QModelIndex Instance);

    QModelIndex insertRow(QModelIndex parent, QJsonTreeItem* child);
    QModelIndex getRootSelection(QModelIndex index);
    void lockInstance(QModelIndex index);

private slots:
    void dataChanged(QModelIndex, QModelIndex);
    void instanceChange(QModelIndex source, QModelIndex group, QStringList path = QStringList());

protected:
    QString RootType;
    QString ItemType;
    QString GroupType;
    QString InstanceType;
    QString OptionType;

    QStringList ItemParentType;
    QStringList GroupParentType;
    QStringList InstanceParentType;
    QStringList OptionParentType;

    QStringList getInstancePath(QModelIndex source, QModelIndex group, QStringList path = QStringList());

};

#endif // EXTENDEDJSONMODEL_H
