//
// Created by murad on 3/14/21.
//

#include "TCPClient.h"

void TCPClient::eraseArr() {
    arr.clear();
}

void TCPClient::setArr(vector<string> &s) {
    arr=s;
}

vector<string> TCPClient::getArr() {
    return arr;
}

bool TCPClient::setup(int port, string& address) {
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        cout << "Could not create socket" << endl;
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (address=="")
    {
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    }
    else if(inet_aton(address.c_str(),&i_addr)!=0)
    {
        addr.sin_addr=i_addr;
    }
    else
    {
        cout<<"address is incorrect";
    }
    if (connect(sock , (struct sockaddr *)&addr , sizeof(addr)) < 0)
    {
        cout<<"connect failed. Error";
        exit(1);
    }

    return true;
}

bool TCPClient::sendTCP(string &data) const {
    if(sock != -1)
    {
        if( send(sock , data.c_str() , data.size() , 0) < 0)
        {
            cout << "Send failed : " << data << endl;
            return false;
        }// TODO проверка на количество отправленных байт
    }
    else
        return false;
    return true;
}

string TCPClient::receive(int size) const {
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

void TCPClient::exitTCP() const {
    close(sock);
}
