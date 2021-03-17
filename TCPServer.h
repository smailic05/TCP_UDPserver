//
// Created by murad on 3/14/21.
//

#ifndef TCP_UDPSERVER_TCPSERVER_H
#define TCP_UDPSERVER_TCPSERVER_H
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include<vector>
#include<cstring>
#include <poll.h>
#include <thread>

using namespace std;

class TCPServer {
private:
    int sock;
    int listener;
    struct sockaddr_in addr;
    struct in_addr i_addr;

public:
    int getListener();
    void closeSock() const;
    int acceptTCP();
    int getSock();
    bool setup(int port);
    static bool sendTCP(string &data, int &sock);
    bool sendTCP(string &data) ;
    string receive(int size) const;
    static string receive(int size, int sock) ;
    void exitTCP() const;
};


#endif //TCP_UDPSERVER_TCPSERVER_H
