#ifndef CONTROLINTERFACE
#define CONTROLINTERFACE

#include <QtCore>
#include <QStringList>
#include <QPair>

//template <typename Val, typename Add>;

class ControlInterface {
public:
    virtual ~ControlInterface() {}

    virtual bool setAddress(QStringList) = 0;
    QStringList getAdress() {return m_address;}

    virtual bool setValue(QString) = 0;
    QString getValue() {return m_value;}

    void setType(QString type) {m_type = type;}
    QString getType() {return m_type;}

    QPair<QString, QString> getBundleValue() {return QPair<QString, QString>(m_type, m_value);}

protected:
    QString m_type;
    QStringList m_address;
    QString m_value;
};

//#define ControlInterfaceIid "vj.rocher.a.ControlInterface"
Q_DECLARE_INTERFACE(ControlInterface, "vj.rocher.a.ControlInterface")

#endif // CONTROLINTERFACE

