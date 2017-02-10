#ifndef CONTROLINTERFACE
#define CONTROLINTERFACE

#include <QtCore>
#include <QStringList>
#include <QPair>
#include "../controlglobal.h"
#include "../helpers/controleventhelper.h"

//template <typename Val, typename Add>;

//using namespace ncontrol::ControlProtocol;

//TODO : Connect Controls to Listeners by GlobalRouter

class ControlInterface : public QObject{
    Q_OBJECT
public:
    ControlInterface() {};
    ~ControlInterface() {}

    bool setAddress(QStringList newAddr) {
        m_address = newAddr;
        return true;
    };
    QStringList getAdress() {return m_address;}

    bool setValue(QVariant newVal) {
        m_value = newVal;
        emit valueChanged(m_value);
        return true;
    }
    QVariant getValue() {return m_value;}

    void setType(ControlProtocol type) {m_type = type;}
    ControlProtocol getType() {return m_type;}

    QString getTypeString(ControlProtocol CP) {
        switch (CP) {
            case 0x01:
                return QString("Osc");
            case 0x02:
                return "Midi";
            case 0x03:
                return "Keyboard";
        }
    }

    QPair<QString, QString> getBundleValue() {
        return QPair<QString, QString>(getTypeString(m_type), m_value.toString());
    }

    /*
    QString getTypedAddress() {
        return QString(getTypeString(m_type)+)
    }
    */

signals:
    void valueChanged (QVariant);

public slots:
    void handleEvent(ListenerEvent* e){Q_UNUSED(e)};

protected:
    ControlProtocol m_type;
    QStringList m_address;
    QVariant m_value;
};

//#define ControlInterfaceIid "vj.rocher.a.ControlInterface"
//Q_DECLARE_INTERFACE(ControlInterface, "vj.rocher.a.ControlInterface")

#endif // CONTROLINTERFACE

