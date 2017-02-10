#ifndef GLOBALROUTER_H
#define GLOBALROUTER_H

#include <QObject>
#include <QList>
#include <QPair>

#include "controlglobal.h"
#include "controls/controlinterface.h"
#include "listeners/listener.h"
#include "helpers/routereventhelper.h"

//class to route listnener to controls with RouterEventHelper's;

class GlobalRouter : public QObject
{
    Q_OBJECT
public:
    static GlobalRouter *Instance();
    explicit GlobalRouter(QObject *parent = 0);

    QSharedPointer<ControlInterface> addControl(ControlProtocol type, QVariant address1, QVariant address2 = 0);

signals:

public slots:

protected:
    bool registerControl(QSharedPointer<ControlInterface>);
private:
    //QList<QPair<Control*,QList< QSharedPointer<ControlInterface> > > > ControlList;

    //int  searchControl(Control* ControlSearch);
    int  searchType(int ControlIndex, ControlProtocol type);

    Listener* getListener(QSharedPointer<ControlInterface>);

    QMap<ControlProtocol, Listener*> mListeners;

    QMap<Listener*, routerEventHelper*> mRoutes;
    QMap<QSharedPointer<ControlInterface> , routerEventHelper*> mRouteObjects;
};

#endif // GLOBALROUTER_H
