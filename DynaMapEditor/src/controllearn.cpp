#include "controllearn.h"
#include "ui_controllearn.h"

ControlLearn::ControlLearn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlLearn)
{
    ui->setupUi(this);
}

ControlLearn::~ControlLearn()
{
    delete ui;
}
