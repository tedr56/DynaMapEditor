#include "instancegroupdialog.h"
#include "ui_instancegroupdialog.h"


InstanceGroupDialog::InstanceGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InstanceGroupDialog)
{
    ui->setupUi(this);
    GroupModel = new FilterJsonProxy(ui->GroupView);
    TreeModel = new FilterJsonProxy(ui->TreeView);
    ui->GroupView->setModel(GroupModel);
    ui->TreeView->setModel(TreeModel);
    connect(ui->GroupView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(GroupSelectionChanged(QItemSelection,QItemSelection)));
    connect(ui->TreeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(TreeSelectionChanged(QItemSelection,QItemSelection)));
    connect(ui->instances, SIGNAL(valueChanged(int)), this, SLOT(InstancesChanged(int)));
    Instances = ui->instances->value();
}

InstanceGroupDialog::~InstanceGroupDialog()
{
    delete ui;
}

void InstanceGroupDialog::setModel(QJsonModel *SourceModel)
{
    GroupModel->setSourceModel(SourceModel);
    TreeModel->setSourceModel(SourceModel);
}

bool InstanceGroupDialog::setGroupParent(QModelIndex GroupParent)
{
    if (GroupParent.parent() == QModelIndex())
    {
        QModelIndex GroupIndex = GroupModel->mapFromSource(GroupParent);
        QModelIndex TreeIndex  = TreeModel->mapFromSource(GroupParent);

        ui->TreeView->setRootIndex(TreeIndex);
        ui->GroupView->setRootIndex(GroupIndex);

        ui->TreeView->hideColumn(1);
        return true;
    }
    if (GroupParent == QModelIndex())
        return false;
    else
        return setGroupParent(GroupParent.parent());
}

void InstanceGroupDialog::setGroupFilter(QStringList TypeFilter)
{
    GroupModel->setItemTypeFilter(TypeFilter, JsonFilter::Accept);
}

void InstanceGroupDialog::setInstanceFilter(QStringList TypeFilter)
{
    TreeModel->setItemTypeFilter(TypeFilter, JsonFilter::Accept);
}

QModelIndex InstanceGroupDialog::getGroupSelection()
{
    return GroupSelection;
}

QModelIndex InstanceGroupDialog::getTreeSelection()
{
    return TreeSelection;
}

int InstanceGroupDialog::getNumInstances()
{
    return Instances;
}

void InstanceGroupDialog::GroupSelectionChanged(QItemSelection new_select, QItemSelection old_select)
{
    Q_UNUSED(old_select);
    if (new_select.indexes().empty())
        return;
    GroupSelection = GroupModel->mapToSource(new_select.indexes().first());
}

void InstanceGroupDialog::TreeSelectionChanged(QItemSelection new_select, QItemSelection old_select)
{
    Q_UNUSED(old_select);
    if (new_select.indexes().empty())
        return;
    TreeSelection = TreeModel->mapToSource(new_select.indexes().first());
}

void InstanceGroupDialog::InstancesChanged(int Value)
{
    Instances = Value;
}

