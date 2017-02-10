#include <iostream>
#include <string>
#include <stdio.h>

#include "oscserver.h"
#include <lo/lo_serverthread.h>

OscServer* OscServer::m_instance = 0;

OscServer::OscServer(int port) : QObject()
{
    m_port = port;
    char port_char [16];
    sprintf(port_char, "%d", m_port);
    m_server = lo_server_thread_new(port_char, error);

}

OscServer::~OscServer()
{

}

int OscServer::getPort()
{
    return m_port;
}

OscServer *OscServer::getInstance()
{
    OscServer* server = new OscServer();
    m_instance = server;
    return m_instance;
}

void OscServer::error(int num, const char *msg, const char *path)
{
    std::cout << "liblo server error " <<num << " in path "<< path << msg << std::endl;
}
