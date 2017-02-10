#ifndef LISTENERKEYBOARD_H
#define LISTENERKEYBOARD_H

#include <QObject>

class ListenerKeyboard : public QObject
{
    Q_OBJECT
public:
    explicit ListenerKeyboard(QObject *parent = 0);

signals:

public slots:
};

#endif // LISTENERKEYBOARD_H