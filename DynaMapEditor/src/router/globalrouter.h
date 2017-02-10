#ifndef GLOBALROUTER_H
#define GLOBALROUTER_H

#include <QObject>

class GlobalRouter : public QObject
{
    Q_OBJECT
public:
    explicit GlobalRouter(QObject *parent = 0);

signals:

public slots:
};

#endif // GLOBALROUTER_H