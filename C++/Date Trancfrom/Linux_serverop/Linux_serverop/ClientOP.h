#pragma once
#include<string>
using namespace std;
struct Clientinfo
{
	string clientId;
	string serverId;
};
class ClientOP
{
public:
	ClientOP(string jsonFile);
	~ClientOP();

	//秘钥协商
	bool seckeyAgree();
	//秘钥检验
	bool seckeyCheck();
	//秘钥注销
	void seckeyZhuxiao();
private:
	Clientinfo m_info;
};