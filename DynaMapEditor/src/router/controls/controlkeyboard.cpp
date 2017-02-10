#include "controlkeyboard.h"

ControlKeyboard::ControlKeyboard()
{
}

bool ControlKeyboard::setAddress(QStringList Address) {
    if (Address.size() == 3) {
        m_address = Address;
        QString types = Address.at(1);
        bool typeSelectSuccess = false;

        int typeSelect = Address.at(2).toInt(&typeSelectSuccess, 10);
        if (typeSelectSuccess) {
            if (typeSelect < types.size()) {
                m_typeSelect = typeSelect;
                QChar type = types.at(typeSelect);
                if (type == 's') {
                    setType("QString");
                } else
                if (type == 'f') {
                    setType("float");
                } else
                if (type == 'i') {
                    setType("int");
                }
                return true;
            }
        }
    }
    return false;
}

bool ControlKeyboard::setValue(QString Value) {
    m_value = Value;
    return true;
}
