#ifndef OSCSERVER_H
#define OSCSERVER_H

#include <lo/lo.h>
#include <QObject>

class OscServer : public QObject
{
    Q_OBJECT
public:
    OscServer(int port = 9999);
    ~OscServer();
    int getPort();
    static OscServer* getInstance();
private:
    static OscServer* m_instance;
    int m_port;
    lo_server m_server;
    static void error(int num, const char *msg, const char *path);
};

#endif // OSCSERVER_H
