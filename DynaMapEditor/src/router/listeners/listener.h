#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>
#include <QVariant>

class Listener : public QObject
{
    Q_OBJECT
public:
    ~Listener() {};
protected:
    explicit Listener(QObject *parent = 0);

signals:

public slots:
};

#endif // LISTENER_H
