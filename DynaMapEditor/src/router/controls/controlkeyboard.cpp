#include "controlkeyboard.h"

ControlKeyboard::ControlKeyboard()
{
}

bool ControlKeyboard::setAddress(QStringList Address) {
    if (Address.size() == 3) {
        m_address = Address;
        QString types = Address.at(1);
        bool typeSelectSuccess = false;
    }
    return false;
}

bool ControlKeyboard::setValue(QString Value) {
    m_value = Value;
    return true;
}
