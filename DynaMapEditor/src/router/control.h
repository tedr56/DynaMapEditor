#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include "router/router.h"


class Control : public QObject
{
    Q_OBJECT
    Q_ENUMS(ControlType)
public:
    enum ControlType {OSC, MIDI, KEYBOARD};

    explicit Control(QObject *parent = 0);
    explicit Control(QObject *parent = 0, ControlType type = OSC);

    void setType(ControlType type);
    bool setAddress(int MidiChannel, int MidiControl);
    bool setAddress(QString OscPath, int OscArgument = 0);
    bool setAddress(int KeyAddress);

signals:
    void valueChanged(bool);
    void valueChanged(int);
    void valueChanged(float);
    void valueChanged(QString);
public slots:
private:
    ControlType m_type;
    //GlobalRouter* m_router;
};

#endif // CONTROL_H
