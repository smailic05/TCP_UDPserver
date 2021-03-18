

#include "TCPServer.h"

void TCPServer::closeSock() const {
    close(sock);
    close(listener);
}

int TCPServer::acceptTCP() {
    sock = accept(listener, NULL, NULL);
    if(sock < 0)
    {
        perror("accept");
        return -1;
    }
    return sock;
}

bool TCPServer::setup(int port) {
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        return false;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return false;
    }

    if(listen(listener, 30)<0)
    {
        perror("listen");
        return false;
    }

    return true;
}

bool TCPServer::sendTCP(string &data)  {
    if(sock != -1)
    {
        int bytes=send(sock , data.c_str() , data.size() , 0);
        if (bytes==-1)
        {
            sock=0;
            return false;
        }
        if( bytes != data.size())
        {
            cout << "Send failed : " << data << endl;
            return false;
        }
    }
    else
        return false;
    return true;
}

string TCPServer::receive(int size) const {
    char buffer[size];
    memset(&buffer[0], 0, sizeof(buffer));
    string reply;
    if( recv(sock , buffer , size, 0) < 0)
    {
        cout << "receive failed!" << endl;
        return nullptr;
    }
    buffer[size-1]='\0';
    reply = buffer;
    return reply;
}

void TCPServer::exitTCP() const {
    close(sock);
}

int TCPServer::getSock() {
    return sock;
}

int TCPServer::getListener() {
    return listener;
}

string TCPServer::receive(int size, int sock) {
    char buffer[size];
    memset(&buffer[0], 0, sizeof(buffer));
    string reply;
    if( recv(sock , buffer , size, 0) < 0)
    {
        cout << "receive failed!" << endl;
        return "";
    }
    buffer[size-1]='\0';
    reply = buffer;
    return reply;
}

bool TCPServer::sendTCP(string &data, int &sock) {
    if(sock != -1)
    {
        int bytes=send(sock , data.c_str() , data.size() , 0);
        if (bytes==-1)
        {
            sock=0;
            return false;
        }
        if( bytes != data.size())
        {
            cout << "Send failed : " << data << endl;
            return false;
        }
    }
    else
        return false;
    return true;
}


