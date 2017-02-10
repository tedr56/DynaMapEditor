#include "controllerscontrolgroupdialog.h"
#include "ui_controllerscontrolgroupdialog.h"
#include <QtUiTools/QUiLoader>
#include <QMouseEvent>
#include <QMessageBox>

#include "learn/controllearn.h"

//Controller management Window
//Opens ControlLearn for Control Editing

ControllersControlGroupDialog::ControllersControlGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllersControlGroupDialog)
{
    ui->setupUi(this);
    ControlProxy = new FilterJsonProxy(ui->ControlTree);
    ui->ControlTree->setModel(ControlProxy);
    QSettings settings;

    ui->LearnMode->setChecked(settings.value("ControllersLearnMode", 0).toBool());
    connect(ui->LearnMode, SIGNAL(clicked(bool)), this, SLOT(setLearnMode(bool)));
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
    connect(ui->ControlAdd, SIGNAL(clicked(bool)), this, SLOT(addControlMode(bool)));
    connect(ui->ControlAdd, SIGNAL(released()), this, SLOT(addControlModeEnd()));

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

void ControllersControlGroupDialog::addControlMode(bool checked)
{
    if (checked) {
        installEventFilter(this);
    } else {
        removeEventFilter(this);
    }
}

void ControllersControlGroupDialog::setLearnMode(bool mode)
{
    QSettings settings;
    settings.setValue("ControllersLearnMode", mode);
}

bool ControllersControlGroupDialog::eventFilter(QObject* object, QEvent* event) {
    Q_UNUSED(object);
    QEvent::Type type = event->type();
    if (type == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = (QMouseEvent*)event;
        QWidget* widget = this->childAt(mouseEvent->pos());
        QString widgetClass = widget->metaObject()->className();

        qDebug() << widgetClass;

        QStringList acceptedWidgetClasses;
        acceptedWidgetClasses << "QDial" << "QPushButton" << "QSlider";

        if (acceptedWidgetClasses.contains(widgetClass)) {
            addControl(widget);
            return true;
        }
    }
    return false;
}

void ControllersControlGroupDialog::addControl(QWidget* widget)
{
    QString name = widget->objectName();
    if (ui->LearnMode->isChecked()) {
        ControlLearn ControlLearnDialog(this);
        ControlLearnDialog.exec();
    }
    else {

    }
}
