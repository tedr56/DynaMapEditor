#include "controlmidi.h"

ControlMidi::ControlMidi()
{
};

bool ControlMidi::setAddress(QStringList Address) {
    if (Address.size() == 3) {
        m_address = Address;
        QString types = Address.at(1);
        bool typeSelectSuccess = false;
    }
    return false;
};

bool ControlMidi::setValue(QString Value) {
    m_value = Value;
    return true;
};
