#ifndef CONTROLKEYBOARD_H
#define CONTROLKEYBOARD_H

//#include <QObject>
#include "controlinterface.h"

class ControlKeyboard : /*public QObject,*/ public ControlInterface {
    Q_OBJECT
    //Q_INTERFACES(ControlInterface)
public:
    ControlKeyboard();
    virtual ~ControlKeyboard() { }

    bool setAddress(QStringList Address);
    bool setValue(QString);
signals:
    void valueChanged(QVariant);
private:
    int m_typeSelect;
};

#endif // CONTROLKEYBOARD_H
