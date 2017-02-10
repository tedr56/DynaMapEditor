#ifndef CONTROLLEARN_H
#define CONTROLLEARN_H

#include <QDialog>
#include <QAbstractButton>
#include "../router/controls/controlinterface.h"

//Control Editing Dialog


namespace Ui {
class ControlLearn;
}

class ControlLearn : public QDialog
{
    Q_OBJECT


public:
    explicit ControlLearn(QWidget *parent = 0);
    ~ControlLearn();

/*
protected:
    ControlInterface* openOscListener(void);
    ControlInterface* openMidiListener(void);
    ControlInterface* openKeyboardListenr(void);
*/

private slots:
    void typeChange(int clickedButton);
    void valueInput(QVariant);

private:
    QSharedPointer<ControlInterface>getControlMonitor();

private:
    QSharedPointer<ControlInterface> ControlMonitor;

    QButtonGroup* ControlTypeGroup;
    int clickedType = 0;
    ControlProtocol DialogControlType[3] = {
        ControlProtocol::OSC,
        ControlProtocol::Midi,
        ControlProtocol::Keyboard
    };
    Ui::ControlLearn *ui;
};

#endif // CONTROLLEARN_H
