#include <iostream>
#include "TCPClient.h"
#include "UDPClient.h"
int main(int argc, char **argv) {
    string address;
    if (argc<3)
    {
        cout<<"please specify type and address of the connection"<<endl;
    }
    if(strcmp(argv[1],"tcp") ==0)
    {
        address="127.0.0.1";
        TCPClient tcpClient;
        tcpClient.setup(PORT,address); //127.0.0.1 for loopback
        while (true)
        {
            string message;
            cin>>message;
            tcpClient.sendTCP(message);
            cout<<tcpClient.receive(1024);
            cout<<"you can input another value"<<endl;
        }
    } else if (strcmp(argv[1],"udp") ==0)
    {
        UDPClient udpClient;
        udpClient.setup(PORT,address); //127.0.0.1 for loopback
        while (true)
        {
            string message;
            getline(cin,message);
            udpClient.sendUDP(message);
            cout<<udpClient.receive(1024);
            cout<<"you can input another value"<<endl;
        }
    }

    return 0;
}
