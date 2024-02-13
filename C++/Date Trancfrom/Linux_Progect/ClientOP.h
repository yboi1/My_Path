#pragma once
#include<string>
#include"Message.pb.h" 
using namespace std;
struct Clientinfo
{
	string clientId;
	string serverId;
	string ip;
	unsigned short port;
};
class ClientOP
{
public:
	ClientOP(string jsonFile);
	~ClientOP();

	//��ԿЭ��
	bool seckeyAgree();
	//��Կ����
	bool seckeyCheck();
	//��Կע��
	void seckeyZhuxiao();
private:
	Clientinfo m_info;
};