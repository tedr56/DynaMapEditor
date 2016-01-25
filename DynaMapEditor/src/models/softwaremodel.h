#ifndef SOFTWAREMODEL_H
#define SOFTWAREMODEL_H

#include "extendedjsonmodel.h"

class QJsonTreeItem;

class SoftwareModel : public ExtendedJsonModel
{
    Q_OBJECT

public:
    explicit SoftwareModel(QObject *parent = 0);
    ~SoftwareModel();

//    bool appendSoftware();
//    bool removeSoftware(QModelIndex index);
//    bool appendItem(QModelIndex parent, QString name);
//    bool removeItem(QModelIndex index);
//    bool appendGroup(QModelIndex parent);
//    bool removeGroup(QModelIndex index);
//    bool appendInstance(QModelIndex parent, QModelIndex Group, int instances);
//    bool removeInstance(QModelIndex Instance);
//    bool insertRow(QModelIndex parent, QJsonTreeItem* child);

protected:


private:
};


#endif // SOFTWAREMODEL_H
