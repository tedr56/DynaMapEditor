#include "controlmodel.h"

ControlModel::ControlModel(QObject *parent) :
    ExtendedJsonModel(
        "Controller",
        "ControlGroup",
        "ControlInstance",
        "Control",
        "ControlOption",
        QStringList() << "Controller" << "ControlGroup",
        QStringList() << "ControlSubdivision",
        QStringList() << "ControlGroup",
        QStringList() << "Control",
        parent
        )
{

}

ControlModel::~ControlModel()
{

}

bool ControlModel::addControlGroup(QModelIndex parent)
{
    QJsonTreeItem* parentItem = getItem(parent);
    if (GroupParentType.contains(parentItem->itemType()))
    {

    }
    return true;
}



