#ifndef LISTENEROSC_H
#define LISTENEROSC_H

#include <QObject>
#include "listener.h"
#include <lo/lo.h>
//#include <lo/lo_cpp.h>
//#include <lo/lo_serverthread.h>
class ListenerOsc : public Listener
{
    Q_OBJECT
public:
    explicit ListenerOsc(QObject *parent = 0);
    int getPort();
    bool setPort(int);
    static ListenerOsc* getInstance();
signals:

public slots:
private:
    static ListenerOsc* m_instance;

    int m_port;
//    lo_server m_server;
    static void error(int num, const char *msg, const char *path);
};

#endif // LISTENEROSC_H
/*
OscServer(int port = 9999);
~OscServer();
int getPort();
static OscServer* getInstance();
private:
static OscServer* m_instance;
int m_port;
lo_server m_server;
*/
