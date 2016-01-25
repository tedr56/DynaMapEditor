#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDomDocument>
#include "ui_mainwindow.h"
#include "models/softwaremodel.h"
#include "models/controlmodel.h"
#include "models/filterjsonproxy.h"

class EditorWindow : public QMainWindow, private Ui::Editor
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

    void manageControl();

    void selection(QItemSelection oldSelection, QItemSelection newSelection);
private:
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
};

#endif // EDITORWINDOW_H
