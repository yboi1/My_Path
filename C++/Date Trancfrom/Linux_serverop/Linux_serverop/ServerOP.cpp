#include "ServerOP.h"
#include<string>
#include"TcpSocket.h"
#include<iostream>
#include<fstream>
#include"RequestFactory.h"
#include"RespondFactory.h"
#include"RespondCodec.h"
#include"RequestCodec.h"
#include<fstream>
#include"RsaCrypto.h"
#include<stdlib.h>
#include<json/json.h>
using namespace std;

ServerOP::ServerOP(string json)
{
	//����json�ļ������ļ�->Value
	ifstream ifs(json);
	Value root;
	Reader r;
	r.parse(ifs, root);
	//��ȡ�ͻ��˺ͷ������˿�ID
	m_serverID = root["ServerId"].asString();
	m_port = root["Port"].asInt();
}

ServerOP::~ServerOP()
{
	if (m_server)
	{
		delete m_server;
	}
}

void ServerOP::startServer()
{
	m_server = new TcpServer;
	m_server->setListen(m_port);
	while (1)
	{
		cout << "�ȴ��ͻ�������..." << endl;
		TcpSocket* tcp = m_server->acceptConn();
		if (tcp = NULL)
		{
			continue;
		}
		pthread_t pid;
		pthread_create(&pid, NULL, working, this);
		m_tcp.insert(make_pair(pid, tcp));

	}


}

string ServerOP::seckeyAgree(RequestMsg* reqMsg)
{
	//0.��ǩ������У�� -> ��Կ���� -> �õ���Կ -
	//���յ��Ĺ�Կ����д�����ش���
	ofstream ofs("public.pem");
	ofs << reqMsg->data();
	//�����ǶԳƼ��ܶ���
	Cryptographic rsa("public.pem", false);

	//������ϣ����
	Hash sha(T_SHA1);
	sha.addData(reqMsg->data());
	bool bl = rsa.rsaVerify(sha.result(),reqMsg->sign());//dataΪ��Կ,signΪǩ��
	RespondInfo info;
	if (bl == false)
	{
		cout << "ǩ��У��ʧ��..." << endl;
		info.status = false;
	}
	else
	{
		//1.��������ַ���
		string key = this->getRandKey(Len16);
		//2.ͨ����Կ����
		string secKey = rsa.rsaPubKeyEncrypt(key);
		//3.��ʼ���ظ�������
		info.clientID = reqMsg->clientid();
		info.data = secKey;
		info.seckeyID = 12;
		info.serverID = m_serverID;
		info.status = true;	
	}
	//4.���л�
	CodecFactory* fac = new RespondFactory(&info);
	Codec* c = fac->createCodec();
	string encMsg = c->encodeMsg();
	//5.��������
	return encMsg;

}

void* ServerOP::working(void* arg)
{
	sleep(1); //ȷ����tcp������뵽map��
	string data = string();
	//ͨ�����������ݵ�this����ת��
	ServerOP* op = (ServerOP*)arg;
	//��op�н�ͨ�ŵ��׽��ֶ���ȡ��
	TcpSocket* tcp = op->m_tcp[pthread_self()];
	//1.���ܿͻ������� -> ����
	string msg = tcp->recvMsg();
	//2.�����л� -> �õ�ԭʼ����
	CodecFactory* fac = new RequestFactory(msg);
	Codec* c = fac->createCodec();
	RequestMsg* req = (RequestMsg*)c->decodeMsg();
	//3.ȡ������
	//�жϿͻ�����ʲô����
	switch (req->cmdtype())
	{
	case 1:
		//��ԿЭ��
		data = op->seckeyAgree(req);
		tcp->sendMsg(data);
		tcp->disConnect();
		op->m_tcp.erase(pthread_self());
		delete tcp;
		break;
	case 2:
		break;
	case 3:
		break;
	}

	//�ͷ���Դ
	delete fac;
	delete c;
	return NULL;
}

string ServerOP::getRandKey(KeyLen len)
{
	srand(time(NULL);
	string RandStr = string();
	int num = 0;
	char* sp = "{};'<>/*-+~";
	for (int i = 0; i < len; ++i)
	{
		num = rand() % 4;
		switch (num)
		{
		case 0:	//'a'-'z'
			RandStr.append(1,'a' + rand() % 32);
			break;
		case 1: //'A'-'Z'
			RandStr.append(1, 'a' + rand() % 32);
			break;
		case 2: //'0'-'9'
			RandStr.append(1, 'a' + rand() % 10);
			break;
		case 3: //�����ַ�
			RandStr.append(1, sp[rand() % strlen(sp)]);
			break;
		}
	}
	return string();
}
