

#include "UDPServer.h"

void UDPServer::closeSock() const {
    close(sock);
}

bool UDPServer::setup(int port) {
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        return false;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return false;
    }

    return true;
}

bool UDPServer::sendUDP(string &data) const {
    socklen_t length=sizeof(struct sockaddr_in);
    if(sock != -1)
    {
        int bytes=sendto(sock , data.c_str() , data.size() , 0,(struct sockaddr *)&addr,length) < 0;

        if( bytes < 0 )
        {
            cout << "Send failed : " << data << endl;
            return false;
        }
    }
    else
        return false;
    return true;
}

string UDPServer::receive(int size) const {
    char buffer[size];
    socklen_t length=sizeof(struct sockaddr_in);
    memset(&buffer[0], 0, sizeof(buffer));
    string reply;
    if(recvfrom(sock , buffer , size, 0, (struct sockaddr *)&addr,&length) < 0)// NOTE after receiving addr=source address
    {
        cout << "receive failed!" << endl;
        return "";
    }
    buffer[size-1]='\0';
    reply = buffer;
    return reply;
}
