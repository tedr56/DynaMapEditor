#include "controllerscontrolgroupdialog.h"
#include "ui_controllerscontrolgroupdialog.h"
#include <QtUiTools/QUiLoader>
#include <QMouseEvent>
#include <QMessageBox>

ControllersControlGroupDialog::ControllersControlGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllersControlGroupDialog)
{
    ui->setupUi(this);
    ControlProxy = new FilterJsonProxy(ui->ControlTree);
    ui->ControlTree->setModel(ControlProxy);
}

ControllersControlGroupDialog::~ControllersControlGroupDialog()
{
    delete ui;
}

void ControllersControlGroupDialog::setControlUI(QString ControlPath)
{
    QFile* UiFile = new QFile("./Controllers/" + ControlPath + ".ui");
    if (!UiFile->exists())
    {
        QMessageBox::warning(this, tr("UI File"),
                             tr("Cannot found file %1:\n%2.")
                             .arg(UiFile->fileName())
                             .arg(UiFile->errorString()));
        this->rejected();
        return;
    }
    if (!UiFile->open(QFile::ReadOnly | QFile::Text))
    {
         QMessageBox::warning(this, tr("SAX Bookmarks"),
                              tr("Cannot read file %1:\n%2.")
                              .arg(UiFile->fileName())
                              .arg(UiFile->errorString()));
         this->rejected();
         return;
    }
    QUiLoader uiLoader;
    ui->ControlUI->layout()->addWidget(uiLoader.load(UiFile));
    connect(ui->ControlAdd, SIGNAL(pressed()), this, SLOT(addControl()));
    return;
}

void ControllersControlGroupDialog::setModel(ControlModel *ControlModel)
{
    ControlProxy->setSourceModel(ControlModel);
}

void ControllersControlGroupDialog::setRoot(QModelIndex rootIndex)
{
    ui->ControlTree->setRootIndex(ControlProxy->mapFromSource(rootIndex));
}

void ControllersControlGroupDialog::addControl()
{
    installEventFilter(this);
}

bool ControllersControlGroupDialog::eventFilter(QObject* object, QEvent* event) {
    QEvent::Type type = event->type();
    if (type == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = (QMouseEvent*)event;
        QWidget* widget = this->childAt(mouseEvent->globalPos());

        qDebug() << widget->inherits("QDial");
        return true;

    }
    return false;
}
