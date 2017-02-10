#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QVariant>
#include "controlglobal.h"


class Control : public QObject
{
    Q_OBJECT
    //Q_ENUMS(ControlType)
public:
    explicit Control(QObject *parent = 0);
    explicit Control(QObject *parent, ControlProtocol type, QVariant* address1, QVariant* address2);

    void AddType(ControlProtocol type);
    void DelType(ControlProtocol type);

    bool setAddress(ControlProtocol type, QVariant *address1, QVariant *address2);
    bool setMidiAddress(int MidiChannel, int MidiControl);
    bool setOscAddress(QString OscPath, int OscArgument = 0);
    bool setKeyAddress(int KeyAddress);

signals:
    void valueChanged(bool);
    void valueChanged(int);
    void valueChanged(float);
    void valueChanged(QString);
public slots:

private:

    //GlobalRouter* m_router;
};

#endif // CONTROL_H
