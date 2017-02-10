#ifndef LISTENERKEYBOARD_H
#define LISTENERKEYBOARD_H

#include <QObject>
#include "listener.h"

class ListenerKeyboard : public Listener
{
    Q_OBJECT
public:
    explicit ListenerKeyboard(QObject *parent = 0);

signals:

public slots:
};

#endif // LISTENERKEYBOARD_H
