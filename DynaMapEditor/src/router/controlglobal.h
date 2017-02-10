#ifndef CONTROLGLOBAL_H
#define CONTROLGLOBAL_H

#include <QtCore>

enum /*class */ControlProtocol {
    OSC = 0x01,
    Midi = 0x02,
    Keyboard = 0x03
};

enum ControlMonitoring {
    Off = 0x00,
    On = 0x01
};

enum class ControlType {
    Bool = 0x01,
    Integer = 0x02,
    Float = 0x03,
    String = 0x04
};

/*
QT_BEGIN_NAMESPACE

namespace ncontrol{

namespace ControlProtocol  {
enum CP {
    OSC = 0x01,
    Midi = 0x02,
    Keyboard = 0x03
};
}

//Q_ENUMS(ControlProtocol);

enum ControlType {
    Bool = 0x01,
    Integer = 0x02,
    Float = 0x03,
    String = 0x04
};


}

//Q_ENUMS(ControlType);

QT_END_NAMESPACE
*/
#endif // CONTROLGLOBAL_H
