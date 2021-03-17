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
    int newClient;
    string toSend;

    thread threadUDP(threadUDPFunc);

    if(!tcpServer.setup(PORT))
    {
        {
            cout<<"can`t TCP create socket on port"<<PORT<<endl;
            exit(1);
        }
    }
    fds[0].fd = tcpServer.getListener();
    fds[0].events = POLLIN;

    while (true) {

        buf.clear();
        int ret = poll(fds, 30, 50000);
        // проверяем успешность вызова
        if (ret == -1)
            cerr << "error" << endl;
        else {
            // обнаружили событие, обнулим revents чтобы можно было переиспользовать структуру
            if (fds[0].revents == POLLIN){
                fds[0].revents = 0;
                newClient = tcpServer.acceptTCP();
                if(newClient>0) {
                    for (int i = 1; i < 30; i++) {
                        if (fds[i].fd == 0) {
                            fds[i].fd = newClient;
                            fds[i].events = POLLIN;
                            break;
                        }
                    }
                    test = TCPServer::receive(1024, newClient);
                    if (test.empty())
                    {
                        toSend="received an empty string";
                        TCPServer::sendTCP(toSend, newClient);
                    }
                    else
                    {
                        arr = split(test, ' ');
                        strToInt(arr, buf);
                        if (buf.empty()) {
                            toSend = "there is a problem with your string, please input only digits";
                        } else {
                            toSend = to_string(sum(buf));
                        }
                        TCPServer::sendTCP(toSend, newClient);
                    }
                }
            }
            else
                {
                for (int i = 1; i < 30; i++) {
                    if (fds[i].revents == POLLIN) {
                        fds[i].revents = 0;
                        test = TCPServer::receive(1024, fds[i].fd);
                        if (test.empty())
                        {
                            toSend="received an empty string";
                            TCPServer::sendTCP(toSend, newClient);
                        }
                        else {
                            arr = split(test, ' ');
                            strToInt(arr, buf);
                            if (buf.empty()) {
                                toSend = "there is a problem with your string, please input only digits";
                            } else {
                                toSend = to_string(sum(buf));
                            }
                            toSend = to_string(sum(buf));
                            TCPServer::sendTCP(toSend, fds[i].fd);

                        }
                    }
                    else
                    {
                        if (fds[i].revents & POLLHUP)
                        {
                            fds[i].fd=0;
                            fds[i].revents = 0;
                        }
                    }
                }

            }
        }

    }
    //TODO safe quit
}
void threadUDPFunc()
{
    vector<string> arr;
    vector<int> buf;
    string rv;
    UDPServer udpServer;
    if(!udpServer.setup(PORT))
    {
        cout<<"can`t UDP create socket on port"<<PORT<<endl;
        exit(1);
    }
    while (true)
    {
        rv=udpServer.receive(1024);
        arr=split(rv,' ');
        strToInt(arr,buf);
        string toSend=to_string(sum(buf));
        udpServer.sendUDP(toSend);
        buf.clear();
    }
}


vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> elements;
    while (getline(ss, item, delim))
    {
        if (!item.empty())
        {
            elements.push_back(item);
        }

    }
    return elements;
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
                buf.clear();
            } else
            {
                cout<<"unknown error";
               buf.clear();
            }
        }
    }
}
