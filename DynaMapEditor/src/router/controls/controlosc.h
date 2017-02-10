#ifndef CONTROLOSC_H
#define CONTROLOSC_H

//#include <QObject>
#include "controlinterface.h"

class ControlOsc : public QObject, public ControlInterface {
    Q_OBJECT
    Q_INTERFACES(ControlInterface)
public:
    ControlOsc();
    virtual ~ControlOsc() { }

    bool setAddress(QStringList Address);
    bool setValue(QString);
private:
    int m_typeSelect;
};

#endif // CONTROLOSC_H
