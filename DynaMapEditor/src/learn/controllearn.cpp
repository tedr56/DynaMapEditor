#include "controllearn.h"
#include "ui_controllearn.h"
#include <QSettings>
#include "../router/globalrouter.h"

ControlLearn::ControlLearn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlLearn)
{
    ui->setupUi(this);
    ControlTypeGroup = new QButtonGroup(this);
    ControlTypeGroup->addButton(ui->MidiRadio, 0);
    ControlTypeGroup->addButton(ui->OscRadio, 1);
    ControlTypeGroup->addButton(ui->KeyboardRadio, 2);

    ControlTypeGroup->setExclusive(true);

    connect(ControlTypeGroup, SIGNAL(buttonClicked(int)), this, SLOT(typeChange(int)));
    connect(ControlTypeGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(typeChange(QAbstractButton*)));

    QSettings settings;
    QRadioButton* selectedTypeButton =  qobject_cast<QRadioButton*>(ControlTypeGroup->button(settings.value("ControlLearnType", 0).toInt()));
    selectedTypeButton->setChecked(true);

    ui->AutoAcceptBox->setChecked(settings.value("ControlLearnAuto", false).toBool());
    typeChange(settings.value("ControlLearnAuto", false).toBool());
}

ControlLearn::~ControlLearn()
{
    QSettings settings;
    settings.setValue("ControlLearnAuto", ui->AutoAcceptBox->checkState());

    delete ui;
}

void ControlLearn::typeChange(int clickedButton)
{
    QSettings settings;
    settings.setValue("ControlLearnType", clickedButton);
    clickedType = clickedButton;
    ControlMonitor = getControlMonitor();
    connect(ControlMonitor.data(), SIGNAL(valueChanged(QVariant)), this, SLOT(valueInput(QVariant)));

}

void ControlLearn::valueInput(QVariant)
{

}

QSharedPointer<ControlInterface> ControlLearn::getControlMonitor()
{
    GlobalRouter* router = GlobalRouter::Instance();
    return router->addControl(DialogControlType[clickedType], ControlMonitoring::On);
}
