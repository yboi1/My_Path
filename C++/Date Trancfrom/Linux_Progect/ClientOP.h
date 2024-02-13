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

	//ÃØÔ¿Ğ­ÉÌ
	bool seckeyAgree();
	//ÃØÔ¿¼ìÑé
	bool seckeyCheck();
	//ÃØÔ¿×¢Ïú
	void seckeyZhuxiao();
private:
	Clientinfo m_info;
};