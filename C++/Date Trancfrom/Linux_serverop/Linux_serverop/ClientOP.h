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

	//��ԿЭ��
	bool seckeyAgree();
	//��Կ����
	bool seckeyCheck();
	//��Կע��
	void seckeyZhuxiao();
private:
	Clientinfo m_info;
};