#include"TcpServer.h"
#include<iostream>
#include<string>
using namespace std;
TcpServer::TcpServer()
{

}
TcpServer::TcpServer(int m_Mfd)
{

}
TcpServer::~TcpServer()
{

}
int TcpServer::Serve_init(int port)
{
    int ret = 0;
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	m_Mfd = socket(AF_INET,SOCK_STREAM,0); //绑定套接字
	if (m_Mfd < 0)
	{
		ret = errno ;
		Socket_Log(__FILE__, __LINE__,SocketLevel[4], ret,"func socket() err");
		return ret;
	}
	int in = 1;
	ret = setsockopt(m_Mfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));	//设置端口复用
	if (ret < 0)
	{
		ret = errno ;
		Socket_Log(__FILE__, __LINE__,SocketLevel[4], ret,"func setsockopt() err");
		return ret;
	}
	ret = bind(m_Mfd,(struct sockaddr*)&servaddr,sizeof(sockaddr));  //绑定
	if (ret < 0)
	{
		ret = errno ;
		Socket_Log(__FILE__, __LINE__,SocketLevel[4], ret,"func bind() err");
		return ret;
	}

	ret = listen(m_Mfd,SOMAXCONN);
	if (ret < 0)
	{
		ret = errno ;
		Socket_Log(__FILE__, __LINE__,SocketLevel[4], ret,"func bind() err");
		return ret;
	}
	return 0;
}
int TcpServer::Accept()
{

}
int TcpServer::sendMsg(string ip,int timeout)
{
    // int ret = 0;
    // ret = write_timeout(m_Mfd,timeout);
    // if(0 == ret)
    // {
    //     int writed = 0;
    //     unsigned char * netdata = (unsigned char *)malloc()
    // }
    
}
string TcpServer::recvMsg()
{

}
void TcpServer::disConnect()
{

}
