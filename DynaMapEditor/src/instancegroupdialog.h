#ifndef INSTANCEGROUPDIALOG_H
#define INSTANCEGROUPDIALOG_H

#include <QDialog>
#include "models/qjsonmodel.h"
#include "models/filterjsonproxy.h"

namespace Ui {
class InstanceGroupDialog;
}

class InstanceGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InstanceGroupDialog(QWidget *parent = 0);
    ~InstanceGroupDialog();
    void setModel(QJsonModel *SourceModel);
    bool setGroupParent(QModelIndex GroupParent);

    void setGroupFilter(QStringList TypeFilter);
    void setInstanceFilter(QStringList TypeFilter);

    QModelIndex getGroupSelection();
    QModelIndex getTreeSelection();
    int         getNumInstances();

private slots:
    void GroupSelectionChanged(QItemSelection,QItemSelection);
    void TreeSelectionChanged(QItemSelection,QItemSelection);
    void InstancesChanged(int Value);

private:
    Ui::InstanceGroupDialog *ui;
    FilterJsonProxy *GroupModel;
    FilterJsonProxy *TreeModel;

    QModelIndex GroupSelection;
    QModelIndex TreeSelection;
    int         Instances;

};

#endif // INSTANCEGROUPDIALOG_H
