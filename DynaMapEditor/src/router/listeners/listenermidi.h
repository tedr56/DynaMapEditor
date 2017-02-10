#ifndef LISTENERMIDI_H
#define LISTENERMIDI_H

#include <QObject>
#include "listener.h"

class ListenerMidi : public Listener
{
    Q_OBJECT
public:
    explicit ListenerMidi(QObject *parent = 0);
};

#endif // LISTENERMIDI_H
