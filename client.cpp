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
        string answer;
        string message;
        TCPClient tcpClient;
        tcpClient.setup(PORT,address); //127.0.0.1 for loopback
        while (true)
        {

            getline(cin,message);
            if(!tcpClient.sendTCP(message))
            {
                cout<<"error, message was not sent"<<endl;
            } else
            {
                cout<<tcpClient.receive(1024)<<endl;
            }
            cout<<"do you want to input another value?y/n"<<endl;
            getline(cin,answer);
            if (answer=="n")
            {
                break;
            } else
            {
                if (answer!="y")
                {
                    cout<<"wrong symbol"<<endl;
                }
            }
            cout<<"you can input another value"<<endl;
        }
    } else if (strcmp(argv[1],"udp") ==0)
    {
        UDPClient udpClient;
        string answer;
        udpClient.setup(PORT,address); //127.0.0.1 for loopback
        while (true)
        {
            string message;
            getline(cin,message);
            if(!udpClient.sendUDP(message))
            {
                cout<<"error, message was not sent"<<endl;
            } else
            {
                cout<<udpClient.receive(1024)<<endl;
            }
            cout<<"do you want to input another value?y/n"<<endl;
            getline(cin,answer);
            if (answer=="n")
            {
                break;
            } else
            {
                if (answer!="y")
                {
                    cout<<"wrong symbol"<<endl;
                }
            }
            cout<<"you can input another value"<<endl;
        }
    }

    return 0;
}
