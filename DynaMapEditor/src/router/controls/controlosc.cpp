#include "controlosc.h"

ControlOsc::ControlOsc()
{
}

bool ControlOsc::setAddress(QStringList Address) {
    if (Address.size() == 3) {
        m_address = Address;
        QString types = Address.at(1);
        bool typeSelectSuccess = false;

        int typeSelect = Address.at(2).toInt(&typeSelectSuccess, 10);
    }
    return false;
}

bool ControlOsc::setValue(QString Value) {
    m_value = Value;
    return true;
}
