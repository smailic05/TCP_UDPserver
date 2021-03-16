//
// Created by murad on 3/14/21.
//

#ifndef TCP_UDPSERVER_UDPSERVER_H
#define TCP_UDPSERVER_UDPSERVER_H
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#define PORT 7777

using namespace std;

class UDPServer {

private:
    int sock;
    int listener;
    struct sockaddr_in addr;
    struct in_addr i_addr;
public:
    void closeSock() const;

    bool setup(int port);
    bool sendUDP(string &data) const;
    string receive(int size) const;
};



#endif //TCP_UDPSERVER_UDPSERVER_H
