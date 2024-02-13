#include<iostream>
#include<string>
using namespace std;
class TcpSocket
{
public:
	TcpSocket();
	TcpSocket(int m_Mfd);
	~TcpSocket();
	int ConnectToHost();
	int sendMsg();
	string recvMsg();
	void disConnect();
private:
	int m_fd;
};