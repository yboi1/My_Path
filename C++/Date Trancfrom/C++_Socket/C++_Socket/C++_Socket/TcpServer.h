#include<iostream>
#include<string>
using namespace std;
class TcpServer
{
public:
    TcpServer();
	TcpServer(int m_Mfd);
	~TcpServer();
	int Serve_init(int port);
    int Accept();
	int sendMsg();
	string recvMsg();
	void disConnect();
private:
    m_Mfd;
};