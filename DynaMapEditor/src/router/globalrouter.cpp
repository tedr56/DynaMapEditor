#include "globalrouter.h"
#include "controls/controlosc.h"
#include "controls/controlmidi.h"
#include "controls/controlkeyboard.h"
#include "listeners/osc/listenerosc.h"
#include "listeners/keyboard/listenerkeyboard.h"

Q_GLOBAL_STATIC(GlobalRouter, GlobalRouterInstance)

GlobalRouter *GlobalRouter::Instance()
{
    return GlobalRouterInstance;
}

GlobalRouter::GlobalRouter(QObject *parent) : QObject(parent)
{

}

QSharedPointer<ControlInterface> GlobalRouter::addControl(ControlProtocol type, QVariant address1, QVariant address2)
{
    //TODO ++ : Search for duplicate with GlobalRouter::SearchControl

    QSharedPointer<ControlInterface> MonoControl;
    if (type == ControlProtocol::OSC) {
        MonoControl = QSharedPointer<ControlInterface>(new ControlOsc());
    } else if (type == ControlProtocol::Midi) {
        MonoControl = QSharedPointer<ControlInterface>(new ControlMidi());
    } else if (type == ControlProtocol::Keyboard) {
        MonoControl = QSharedPointer<ControlInterface>(new ControlKeyboard());
    }
    registerControl(MonoControl);
    return MonoControl;
}

bool GlobalRouter::registerControl(QSharedPointer<ControlInterface> ControlPt)
{
    Listener *listener = getListener(ControlPt);
    if (!listener) {
        return false;
    }
    routerEventHelper *o = mRoutes[listener];

    // if we don't have helper object, create one
    if (o == NULL)
    {
        // create an EventRouterHelper which we use to hook onto
        // the signals and events
        o = new routerEventHelper();
        mRoutes[listener] = o;
    }

    // now connect up all signals and slots between processor and event helper
    connect(o, SIGNAL(event(ListenerEvent*)), ControlPt.data(), SLOT(handleEvent(ListenerEvent*)));

    mRouteObjects[ControlPt] = o;
    return true;
}

/*int GlobalRouter::searchControl(Control *ControlSearch)
{
    int result = -1;

    for (int i = 0; i < ControlList.length(); i ++) {
        if (ControlSearch == ControlList.value(i).first) {
            result = i;
            break;
        }
    }
    return result;
}
*/

int GlobalRouter::searchType(int ControlIndex, ControlProtocol type)
{
    /*if (ControlList.length() < ControlIndex) {
        return false;
    }
    QList<QSharedPointer<ControlInterface> > ControlTypes = ControlList.value(ControlIndex).second;
    foreach (QSharedPointer<ControlInterface> MonoControl , ControlTypes) {
        ControlInterface* MonoControlInt = MonoControl.data();
//        if (MonoControlInt->getType() == type) {
//            return true;
//        }
    }
    */
    return true;
}

Listener *GlobalRouter::getListener(QSharedPointer<ControlInterface> ControlPt)
{
    ControlInterface *Control = ControlPt.data();
    switch (Control->getType()) {
        case ControlProtocol::OSC:
            if (!mListeners.contains(ControlProtocol::OSC)) {
                //ListenerOsc oscListener();
                ListenerOsc* oscListener = new ListenerOsc();
                Listener* listener = dynamic_cast<Listener*>(oscListener);
                //mListeners[ControlProtocol::OSC] =
            }
    }
}

