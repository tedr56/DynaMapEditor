#ifndef CONTROLEVENTHELPER_H
#define CONTROLEVENTHELPER_H

#include <QObject>

class ListenerEvent : public QObject
{
    Q_OBJECT

public:
    ListenerEvent();
};

template <class T>
        class EventHelper
{
    public:
        static QString type()
        {
            return T::staticMetaObject.className();
        }

        static QString type(QObject *e)
        {
            return e->metaObject()->className();
        }
};

#endif
