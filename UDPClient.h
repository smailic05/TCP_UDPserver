

#ifndef TCP_UDPSERVER_UDPCLIENT_H
#define TCP_UDPSERVER_UDPCLIENT_H
#define PORT 7777

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include<vector>
#include<cstring>
#include<sstream>

using namespace std;

class UDPClient {
private:
    vector<string> arr;
    int sock;
    struct sockaddr_in addr;
    struct in_addr i_addr;
public:
    void eraseArr();                        //
    void setArr(vector<string> &s);          //
    vector<string> getArr();                // is it necessary?
    bool setup(int port,string& address);
    bool sendUDP(string &data) const;
    string receive(int size) const;
    void exitTCP() const;
};


#endif //TCP_UDPSERVER_UDPCLIENT_H
