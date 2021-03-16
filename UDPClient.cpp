//
// Created by murad on 3/14/21.
//

#include "UDPClient.h"

void UDPClient::eraseArr() {
    arr.clear();
}

void UDPClient::setArr(vector<string> &s) {
    arr=s;
}

vector<string> UDPClient::getArr() {
    return arr;
}

bool UDPClient::setup(int port, string &address) {
    sock = socket(AF_INET , SOCK_DGRAM , 0);
    if (sock == -1)
    {
        cout << "Could not create socket" << endl;
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (address.empty())
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

    return true;
}

bool UDPClient::sendUDP(string &data) const {
    socklen_t length=sizeof(struct sockaddr_in);
    if(sock != -1)
    {
        if( sendto(sock , data.c_str() , data.size() , 0,(struct sockaddr *)&addr,length) < 0)
        {
            cout << "Send failed : " << data << endl;
            return false;
        }
    }
    else
        return false;
    return true;
}

string UDPClient::receive(int size) const {
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

void UDPClient::exitTCP() const {
    close(sock);
}
