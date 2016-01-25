#ifndef CONTROLLERSCONTROLGROUPDIALOG_H
#define CONTROLLERSCONTROLGROUPDIALOG_H

#include <QDialog>
#include "models/controlmodel.h"
#include "models/filterjsonproxy.h"

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
    void addControl();
//    void delControl();
//    void addGroup();
//    void delGroup();
//    void addClone();
//    void delClone();

private:
    Ui::ControllersControlGroupDialog *ui;
    FilterJsonProxy* ControlProxy;
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // CONTROLLERSCONTROLGROUPDIALOG_H
