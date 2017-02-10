#ifndef CONTROLMIDI_H
#define CONTROLMIDI_H

//#include <QObject>
#include "controlinterface.h"

class ControlMidi : /*public QObject,*/ public ControlInterface {
    Q_OBJECT
    //Q_INTERFACES(ControlInterface)
public:
    ControlMidi();
    virtual ~ControlMidi() { }

    bool setAddress(QStringList Address);
    bool setValue(QString);
signals:
    void valueChanged(QVariant);
private:
    int m_typeSelect;
};

#endif // CONTROLMIDI_H
