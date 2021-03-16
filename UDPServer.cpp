//
// Created by murad on 3/14/21.
//


#include "UDPServer.h"

void UDPServer::closeSock() const {
    close(sock);
}

bool UDPServer::setup(int port) {
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1); //TODO make return instead of exit
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    return true;
}

bool UDPServer::sendUDP(string &data) const {
    socklen_t length=sizeof(struct sockaddr_in);
    if(sock != -1)
    {
        if( sendto(sock , data.c_str() , data.size() , 0,(struct sockaddr *)&addr,length) < 0) //TODO check all existed errors
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
    if(recvfrom(sock , buffer , size, 0, (struct sockaddr *)&addr,&length) < 0)
    {
        cout << "receive failed!" << endl;
        return "";
    }
    buffer[size-1]='\0';
    reply = buffer;
    return reply;
}
