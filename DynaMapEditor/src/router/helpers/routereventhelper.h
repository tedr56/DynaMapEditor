#ifndef ROUTEREVENTHELPER_H
#define ROUTEREVENTHELPER_H

#include <QObject>
#include "controleventhelper.h"

class routerEventHelper : public QObject
{
    Q_OBJECT
public:
    routerEventHelper(QObject* parent = NULL);

signals:
    void event(ListenerEvent* e);

public slots:
    void fireEvent(ListenerEvent* e) { emit event(e);}
};

#endif // ROUTEREVENTHELPER_H
