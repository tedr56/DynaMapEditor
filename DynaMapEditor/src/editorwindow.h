#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDomDocument>
#include "ui_mainwindow.h"
#include "models/softwaremodel.h"
#include "models/controlmodel.h"
#include "models/filterjsonproxy.h"

//FIXED : Add Controller File Open/Save
//TODO : Add connect QModelIndexList for Instance autochange from SoftwareGroups
//TODO : Support %n for osc path
//TODO : Support %i (instances) fields/value
//TODO : Add Midi/OSC sender for Software Learn
//TODO : Sort SoftwareItem/ Path by Name for SLOT(dataChanged)


namespace Ui {
class EditorWindow;
}

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorWindow(QWidget *parent = 0);
    ~EditorWindow();

private slots:
    // Software SLOTS
    void saveSoftware();
    void saveSelection();

    void addSoftware();
    void delSoftware();

    void addSoftwareItem();
    void delSoftwareItem();

    void addSoftwareGroup();
    void delSoftwareGroup();

    void addSoftwareInstance();
    void delSoftwareInstance();

    void hideSoftwareOptions(bool);
    void hideSoftwareGroups(bool);

    //Controller SLOTS
    void addControlUI();
    void loadControlUI();
    void saveControlFile();
    void manageControl();

    void selection(QItemSelection oldSelection, QItemSelection newSelection);
private:
    void addControlUI(QString sourceUiPath);

    FilterJsonProxy* SoftwaresProxy;
    SoftwareModel* Softwares;

    ControlModel* Controllers;
    QString currentControl;

    void selectSoftwareRow(QModelIndex index);
    void expandSoftwareRow(QModelIndex index);

    QModelIndex getSourceSelection();
    QModelIndex getSourceIndex(QModelIndex filterIndex);
    QModelIndex getFilterIndex(QModelIndex sourceIndex);

    void clearLayout(QLayout * Layout);

    Ui::Editor *ui;
};

#endif // EDITORWINDOW_H
