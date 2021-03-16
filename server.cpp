#include <iostream>
#include <sstream>
#include "TCPServer.h"
#include "UDPServer.h"

vector<string> split(const string &s, char delim);
void strToInt(vector<string> &arr,vector<int> &buf);
int sum(vector<int> num);
void threadUDPFunc();


int main(int argc, char **argv) {
    TCPServer tcpServer;
    vector<string> arr;
    vector<int> buf;
    struct pollfd fds[30];
    string test;
    int new_client;

    thread threadUDP(threadUDPFunc);

    tcpServer.setup(PORT);
    fds[0].fd = tcpServer.getListener();
    fds[0].events = POLLIN;

    while (true) {


        int ret = poll(fds, 30, 80000000);
        // проверяем успешность вызова
        if (ret == -1)
            cerr << "error" << endl;
        else {
            // обнаружили событие, обнулим revents чтобы можно было переиспользовать структуру
            if (fds[0].revents == POLLIN) {
                fds[0].revents = 0;
                new_client = tcpServer.acceptTCP();
                for (int i = 1; i < 30; i++) {
                    if (fds[i].fd == 0) {
                        fds[i].fd = new_client;
                        fds[i].events = POLLIN;
                        break;
                    }
                }
                test = TCPServer::receive(1024, new_client);
                arr=split(test,' ');
                strToInt(arr,buf);
                string toSend=to_string(sum(buf));
                TCPServer::sendTCP(toSend,new_client);
            }
            else
                {
                for (int i = 1; i < 30; i++) {
                    if (fds[i].revents == POLLIN) {
                        fds[i].revents = 0;
                        test = TCPServer::receive(1024, fds[i].fd);
                        arr=split(test,' ');
                        strToInt(arr,buf);
                        string toSend=to_string(sum(buf));
                        TCPServer::sendTCP(toSend,fds[i].fd);
                    }
                    else
                    {
                        if (fds[i].revents == POLLHUP)
                        {
                            fds[i].fd=0;
                            fds[i].revents = 0;
                        }
                    }
                    // TODO check if client hung up
                }

            }
        }

    }
    //TODO safe quit
    // TODO sum in loop?
}
void threadUDPFunc()
{
    vector<string> arr;
    vector<int> buf;
    string rv;
    UDPServer udpServer;
    udpServer.setup(PORT);
    while (true)
    {
        rv=udpServer.receive(1024);
        arr=split(rv,' ');
        strToInt(arr,buf);
        string toSend=to_string(sum(buf));
        udpServer.sendUDP(toSend);
    }
}


vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> elems;
    while (getline(ss, item, delim))
    {
        if (item!="") //TODO strcmp all!!
        {
            elems.push_back(item);
        }

    }
    return elems;
}

int sum(vector<int> num)
{
    int val=0;
    for (auto &i:   num)
    {
        val+=i;
    }
    return val;
}

void strToInt(vector<string> &arr,vector<int> &buf)
{
    for (auto & i : arr)
    {
        try
        {
            buf.push_back(stoi(i)); //string to int massive
        }
        catch(const std::exception& e)
        {
            std::cerr<<"error " << '\n';
            if ( e.what()=="stoi")
            {
                cout<< "there is a problem with your string, please input only digits";
            }
            exit(3);
        }
    }
}
