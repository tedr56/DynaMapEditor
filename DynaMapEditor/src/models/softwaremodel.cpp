#include "softwaremodel.h"
#include <QIODevice>

SoftwareModel::SoftwareModel(QObject *parent)
    : ExtendedJsonModel(
          "Software",
          "SoftwareGroup",
          "SoftwareInstance",
          "SoftwareItem",
          "SoftwareItemOption",
          QStringList("Software"),
          QStringList() << "Software" << "SoftwareGroup" << "SoftwareItem",
          QStringList() << "Software" << "SoftwareGroup" << "SoftwareItem",
          QStringList() << "Software" << "SoftwareGroup" << "SoftwareItem" << "SoftwareInstance",
          parent
          )
{
}

SoftwareModel::~SoftwareModel()
{
}
