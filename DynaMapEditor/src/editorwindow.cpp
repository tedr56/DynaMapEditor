#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QtUiTools/QUiLoader>
#include "editorwindow.h"

#include "models/softwaretypedelegate.h"
#include "models/qjsonmodel.h"
#include "instancegroupdialog.h"
#include "controllerscontrolgroupdialog.h"

//TODO : Add connect QModelIndexList for Instance autochange from SoftwareGroups
//TODO : Support %n for osc path
//TODO : Support %i (instances) fields/value
//TODO : Add Midi/OSC sender for Software Learn
//TODO : Sort SoftwareItem/ Path by Name for SLOT(dataChanged)

EditorWindow::EditorWindow(QWidget *parent) :
QMainWindow(parent)
{
    setupUi(this);

    QStringList headers;
    headers << tr("Title") << tr("Type") << tr("Instances") << tr("Osc") << tr("Midi");

    SoftwaresProxy = new FilterJsonProxy(this);
    Softwares = new SoftwareModel(this);
    Softwares->load(":/SoftwareTree.json");

    SoftwaresProxy->setSourceModel(Softwares);
    SoftwareTree->setModel(SoftwaresProxy);

//    SoftwareTree->setSortingEnabled(true);
//    SoftwareTree->sortByColumn(0);

    Controllers = new ControlModel(this);

    //Headbar Connections
    connect(actionSave_Software_File, SIGNAL(triggered()), this, SLOT(saveSoftware()));
    connect(actionSave_Selection, SIGNAL(triggered()), this, SLOT(saveSelection()));
    connect(actionHide_Options, SIGNAL(toggled(bool)), this, SLOT(hideSoftwareOptions(bool)));
    connect(actionHide_Groups, SIGNAL(toggled(bool)), this, SLOT(hideSoftwareGroups(bool)));

    connect(actionOpen_Controller_UI, SIGNAL(triggered()), this, SLOT(addControlUI()));

    //Software Buttons Connection
    connect(SoftAdd, SIGNAL(clicked()), this, SLOT(addSoftware()));
    connect(SoftDel, SIGNAL(clicked()), this, SLOT(delSoftware()));
    connect(SoftItemAdd, SIGNAL(clicked()), this, SLOT(addSoftwareItem()));
    connect(SoftItemDel , SIGNAL(clicked()), this, SLOT(delSoftwareItem()));
    connect(SoftGroupAdd, SIGNAL(clicked()), this, SLOT(addSoftwareGroup()));
    connect(SoftGroupDel, SIGNAL(clicked()), this, SLOT(delSoftwareGroup()));
    connect(SoftInstanceAdd, SIGNAL(clicked()), this, SLOT(addSoftwareInstance()));
    connect(SoftInstanceDel, SIGNAL(clicked()), this, SLOT(delSoftwareInstance()));

    //Controllers Buttons Connections
    connect(ControllerControls, SIGNAL(clicked()), this, SLOT(manageControl()));
    //Debug
    //connect(SoftwareTree->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(selection(QItemSelection,QItemSelection)));
}

EditorWindow::~EditorWindow()
{

}

void EditorWindow::saveSoftware()
{
    //const QFileDialog::Options options = QFlag(fileDialogOptionsWidget->value());
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                tr("QFileDialog::getSaveFileName()")
                                /*saveFileNameLabel->text(),
                                tr("All Files (*);;Json Files (*.json)"),
                                &selectedFilter*/);
    if (!fileName.isEmpty())
    {
        Softwares->save(fileName);
    }
}

void EditorWindow::saveSelection()
{
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                tr("QFileDialog::getSaveFileName()")
                                /*saveFileNameLabel->text(),
                                tr("All Files (*);;Json Files (*.json)"),
                                &selectedFilter*/);
    if (!fileName.isEmpty())
    {
        Softwares->save(fileName, getSourceSelection());
    }
}

void EditorWindow::addSoftware()
{
    QModelIndex newRoot = Softwares->appendRoot();
    selectSoftwareRow(newRoot);
}

void EditorWindow::delSoftware()
{
    QModelIndex Selection = getSourceSelection();
    Softwares->removeRoot(Selection);
    SoftwaresProxy->resetFilter();
}

void EditorWindow::addSoftwareItem()
{
    QModelIndex Selection = getSourceSelection();
    QModelIndex newItem = Softwares->appendItem(Selection, "newItem");
    selectSoftwareRow(newItem);
}

void EditorWindow::delSoftwareItem()
{

    QModelIndex Selection = getSourceSelection();
    Softwares->removeItem(Selection);
    SoftwaresProxy->resetFilter();
}

void EditorWindow::addSoftwareGroup()
{
    QModelIndex Selection = getSourceSelection();
    Softwares->appendGroup(Selection);
}

void EditorWindow::delSoftwareGroup()
{
    QModelIndex Selection = getSourceSelection();
    Softwares->removeGroup(Selection);
    SoftwaresProxy->resetFilter();
}

void EditorWindow::addSoftwareInstance()
{
    InstanceGroupDialog dialog(this);
    dialog.setModel(Softwares);
    QModelIndex Selection = getSourceSelection();
    if (!dialog.setGroupParent(Selection))
        return;
    dialog.setGroupFilter(QStringList() << "SoftwareGroup" << "Software");
    dialog.setInstanceFilter(QStringList() << "Software" << "SoftwareGroup" << "SoftwareItem");

    if (dialog.exec() == QDialog::Accepted)
    {
        QModelIndex GroupSelect = dialog.getGroupSelection();
        QModelIndex TreeSelect = dialog.getTreeSelection();
        int Instances = dialog.getNumInstances();
        SoftwareTree->selectionModel()->clear();
        SoftwareTree->scrollTo(GroupSelect);
        SoftwareTree->scrollTo(TreeSelect);
        SoftwareTree->selectionModel()->select(getFilterIndex(GroupSelect), QItemSelectionModel::Select | QItemSelectionModel::Rows);
        SoftwareTree->selectionModel()->select(getFilterIndex(TreeSelect), QItemSelectionModel::Select | QItemSelectionModel::Rows);
        QModelIndex newSelection = Softwares->appendInstance(TreeSelect, GroupSelect, Instances);
        selectSoftwareRow(newSelection);
    }
}

void EditorWindow::delSoftwareInstance()
{
    QModelIndex Selection = getSourceSelection();
    QModelIndex newSelection = Softwares->removeInstance(Selection);
    selectSoftwareRow(newSelection);
}

void EditorWindow::hideSoftwareOptions(bool checked)
{
    if (checked)
    {
        SoftwaresProxy->setItemTypeFilter("SoftwareItemOption");
    }
    else
    {
        SoftwaresProxy->setItemTypeFilter("SoftwareItemOption", JsonFilter::Reject, JsonFilter::Del);
    }
}

void EditorWindow::hideSoftwareGroups(bool checked)
{
    if (checked)
    {
        SoftwaresProxy->setItemTypeFilter("SoftwareGroup");
    }
    else
    {
        SoftwaresProxy->setItemTypeFilter("SoftwareGroup", JsonFilter::Reject, JsonFilter::Del);
    }
}

void EditorWindow::addControlUI()
{
    QString ApplicationPath = QApplication::applicationDirPath();

    QString selectedFilter;
    QString sourceUiPath = QFileDialog::getOpenFileName(this,
                                tr("QFileDialog::getOpenFileName()"),
                                ApplicationPath,
                                tr("Qt UI Files (*.ui)"),
                                &selectedFilter);
    qDebug() << "Filename: " << sourceUiPath;
    if (sourceUiPath.isEmpty())
    {
        return;
    }

    //Backup directory for UI/Json files
    if (!QDir("Controllers").exists())
    {
        QDir().mkdir("Controllers");
    }

    QFileInfo fileInfo(sourceUiPath);


    QFile sourceUIFile(sourceUiPath);
    if (!sourceUIFile.open(QFile::ReadOnly | QFile::Text))
    {
         QMessageBox::warning(this, tr("UI File"),
                              tr("Cannot read file %1:\n%2.")
                              .arg(sourceUIFile.fileName())
                              .arg(sourceUIFile.errorString()));
         return;
    }

    //Test XML UI File
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument domDocument;
    if (!domDocument.setContent(&sourceUIFile, true, &errorStr, &errorLine, &errorColumn)) {
        QMessageBox::information(window(), tr("UI File"),
            tr("Parse error at line %1, column %2:\n%3")
            .arg(errorLine)
            .arg(errorColumn)
            .arg(errorStr));
        sourceUIFile.close();
        return;
    }
    QDomElement root = domDocument.documentElement();
    if (root.tagName() != "ui")
    {
        QMessageBox::information(window(), tr("UI File"),
                                 tr("The file is not an UI file."));
        return;
    }
    else
    {
        qDebug() << "UI file ok";
    }

    QFile destinationUIFile(ApplicationPath + "/Controllers/" + fileInfo.fileName());
    if (destinationUIFile.exists())
    {
        QMessageBox msgBox(QMessageBox::Warning, tr("QMessageBox::warning()"), tr("Ui File already exists"), 0, this);
        msgBox.addButton(tr("&Override"), QMessageBox::AcceptRole);
        msgBox.addButton(tr("&Cancel"), QMessageBox::RejectRole);
        if (msgBox.exec() == QMessageBox::AcceptRole)
            sourceUIFile.copy(ApplicationPath + "/Controllers/" + fileInfo.fileName());
    }
    else
    {
        sourceUIFile.copy(ApplicationPath + "/Controllers/" + fileInfo.fileName());
    }
    sourceUIFile.close();
    destinationUIFile.close();

    //Json associated to UI file
    QString sourceJsonPath = fileInfo.absolutePath() + "/" + fileInfo.baseName() + ".json";
    QJsonDocument JsonDocument = QJsonDocument();
    if (QFile(sourceJsonPath).exists())
    {
        QFile sourceJsonFile(sourceJsonPath);
        if (!sourceJsonFile.open(QFile::ReadOnly | QFile::Text))
        {
             QMessageBox::warning(this, tr("Json File"),
                                  tr("Cannot read file %1:\n%2.")
                                  .arg(sourceJsonFile.fileName())
                                  .arg(sourceJsonFile.errorString()));
             return;
        }
        sourceJsonFile.copy(ApplicationPath + "Controllers" + fileInfo.baseName() + ".json");
        JsonDocument.fromJson(sourceJsonFile.readAll());
        sourceJsonFile.close();
    }
    else
    {
        qDebug() << fileInfo.baseName();
        Controllers->appendRoot(fileInfo.baseName());
//        QJsonObject rootObject = QJsonObject();
//        rootObject.insert(fileInfo.baseName() , QJsonValue());
//        JsonDocument.setObject(rootObject);
    }
    ControllerTree->setModel(Controllers);
    Controllers->loadJson(JsonDocument.toJson());

    QUiLoader UILoader;
    QFile controller("Controllers/" + fileInfo.fileName());
    controller.open(QFile::ReadOnly | QFile::Text);
    clearLayout(ControllerUI->layout());
    ControllerUI->layout()->addWidget(UILoader.load(&controller, ControllerUI));
    currentControl = fileInfo.baseName();
    controller.close();
    return;
}

void EditorWindow::loadControlUI()
{
    QModelIndex Select = ControllerTree->selectionModel()->selectedIndexes()[0];
    QModelIndex SelectRoot = Controllers->getRootSelection(Select);
    QString Key = Controllers->data(SelectRoot, Qt::DisplayRole).toString();
    qDebug() << Key;
    if (Key == currentControl)
        return;
    QFile controllerUIFile("./Controllers/" + Key + ".ui");
    if (!controllerUIFile.exists())
    {
         QMessageBox::warning(this, tr("UI File"),
                              tr("Cannot found file %1:\n%2.")
                              .arg(controllerUIFile.fileName())
                              .arg(controllerUIFile.errorString()));
         return;
    }
    if (!controllerUIFile.open(QFile::ReadOnly | QFile::Text))
    {
         QMessageBox::warning(this, tr("UI File"),
                              tr("Cannot read file %1:\n%2.")
                              .arg(controllerUIFile.fileName())
                              .arg(controllerUIFile.errorString()));
         return;
    }
    QUiLoader UiLoader;
    clearLayout(ControllerUI->layout());
    ControllerUI->layout()->addWidget(UiLoader.load(&controllerUIFile, ControllerUI));
    controllerUIFile.close();
}

void EditorWindow::manageControl()
{
    ControllersControlGroupDialog ControlDialog(this);
    if (!currentControl.size())
    {
        QMessageBox::warning(this, tr("UI File"),
                             tr("No Controller Selected"));
        return;
    }
    ControlDialog.setControlUI(currentControl);
    ControlDialog.setModel(Controllers);
    //ControlDialog.setRoot(ControllerTree->selectionModel()->selectedIndexes()[0]);
    ControlDialog.exec();
}

QModelIndex EditorWindow::getSourceSelection()
{
    QModelIndexList selection = SoftwareTree->selectionModel()->selectedIndexes();
    if (selection.size())
        return getSourceIndex(selection[0]);
    else
        return getSourceIndex(QModelIndex());
}

QModelIndex EditorWindow::getSourceIndex(QModelIndex filterIndex)
{
    return SoftwaresProxy->mapToSource(filterIndex);
}

QModelIndex EditorWindow::getFilterIndex(QModelIndex sourceIndex)
{
    return SoftwaresProxy->mapFromSource(sourceIndex);
}

void EditorWindow::clearLayout(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0) {
        if(child->layout() != 0)
            clearLayout( child->layout() );
        else if(child->widget() != 0)
            delete child->widget();

        delete child;
    }
}

void EditorWindow::selection(QItemSelection oldSelection, QItemSelection newSelection)
{
    Q_UNUSED(oldSelection);
    Q_UNUSED(newSelection);
}

void EditorWindow::selectSoftwareRow(QModelIndex index)
{
    SoftwareTree->selectionModel()->clearSelection();
    QModelIndex filterIndex = getFilterIndex(index);
    SoftwareTree->selectionModel()->select(filterIndex, QItemSelectionModel::Select | QItemSelectionModel::Rows);
    expandSoftwareRow(filterIndex);
}

void EditorWindow::expandSoftwareRow(QModelIndex index)
{
    if (index == QModelIndex())
    {
        return;
    }
    else
    {
        SoftwareTree->expand(index);
        expandSoftwareRow(index.parent());
    }
}
