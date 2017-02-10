#ifndef CONTROLLERSCONTROLGROUPDIALOG_H
#define CONTROLLERSCONTROLGROUPDIALOG_H

#include <QDialog>
#include "models/controlmodel.h"
#include "models/filterjsonproxy.h"

//Controller management Window
//Opens ControlLearn for Control Editing

namespace Ui {
class ControllersControlGroupDialog;
}

class ControllersControlGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ControllersControlGroupDialog(QWidget *parent = 0);
    ~ControllersControlGroupDialog();
    void setControlUI(QString ControlPath);
    void setModel(ControlModel* ControlModel);
    void setRoot(QModelIndex rootIndex);

public slots:
    void addControlMode(bool checked);
//    void delControl();
//    void addGroup();
//    void delGroup();
//    void addClone();
//    void delClone();
    void setLearnMode(bool);
private:
    Ui::ControllersControlGroupDialog *ui;
    FilterJsonProxy* ControlProxy;
    bool eventFilter(QObject *object, QEvent *event);

    void addControl(QWidget* widget);
};

#endif // CONTROLLERSCONTROLGROUPDIALOG_H
