#include"TcpSocket.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
using namespace std;
TcpSocket::TcpSocket()
{

}
TcpSocket::TcpSocket(int m_Mfd)
{
	this->m_Mfd = m_Mfd;
}
TcpSocket::~TcpSocket()
{

}
int TcpSocket::ConnectToHost(int port)
{
	
}
int TcpSocket::sendMsg()
{

}
string TcpSocket::recvMsg()
{
	
}
void TcpSocket::disConnect()
{
	close(m_Mfd);
}