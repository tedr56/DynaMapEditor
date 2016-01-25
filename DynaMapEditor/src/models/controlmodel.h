#ifndef CONTROLMODEL_H
#define CONTROLMODEL_H

#include "extendedjsonmodel.h"

class ControlModel : public ExtendedJsonModel
{
public:
    explicit ControlModel(QObject *parent = 0);
    ~ControlModel();
    bool addControlGroup(QModelIndex parent);
    bool removeControlGroup(QModelIndex parent);
    bool addControllerSubdivision(QModelIndex parent);
    bool removeControllerSubdivision(QModelIndex parent);
};

#endif // CONTROLMODEL_H
