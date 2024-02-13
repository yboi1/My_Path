#include"ClientOP.h"
#include<json/json.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include"RequestCodec.h"
#include"RequestFactory.h"
#include"TcpSocket.h"
#include"RsaCrypto.h"
#include"RespondFactory.h"
#include"RespondCodec.h"
#include "Hash.h"
using namespace Json;
using namespace std;
ClientOP::ClientOP(string jsonFile)
{
	//����json�ļ������ļ�->Value
	ifstream ifs(jsonFile);
	Value root;
	Reader r;
	r.parse(ifs, root);
	//��ȡ�ͻ��˺ͷ������˿�ID
	m_info.clientId = root["ClientId"].asString();
	m_info.serverId = root["ServerId"].asString();
	m_info.ip = root["ip"].asString();
	m_info.port = root["port"].asInt();

}
ClientOP::~ClientOP()
{
}
bool ClientOP::seckeyAgree()
{
	//0.������Կ�ԣ�����Կ�ַ�������
	Cryptographic rsa;
	//������Կ��
	rsa.generateRsakey(1024);
	//����Կ�ļ�
	ifstream ifs("public.pem");
	stringstream str;
	str << ifs.rdbuf();
	//��ʼ��ϵ�л�����
	RequestInfo reqInfo;
	reqInfo.clientID = m_info.clientId;
	reqInfo.serverID = m_info.serverId;
	reqInfo.cmd = 1;	//��ԿЭ��
	reqInfo.data = str.str();	//�ǶԳƼ��ܵ���Կ
	//reqInfo.sign = rsa.rsaSign(str.str());	//ǩ��
	//������ϣ����
	Hash sha1(T_SHA1);
	sha1.addData(str.str());
	reqInfo.sign = rsa.rsaSign(sha1.result());
	cout << "ǩ�����" << endl;
	CodecFactory* factory = new RequestFactory(&reqInfo);
	Codec* c = factory->createCodec();
	//�õ����л�������ݣ����Խ��䷢�͸��ͻ���
	string encstr = c->encodeMsg();		//����������
	//�ͷ���Դ
	delete factory;
	delete c;

	//�ͻ������ӷ�����
	TcpSocket* tcp = new TcpSocket;
	//���ӷ������������ļ�
	//connectToHost(string ip, unsigned short port, int timeout)
	int ret = tcp->connectToHost(m_info.ip, m_info.port);
	if (ret != 0)
	{
		cout << "���ӷ�����ʧ��"
			<< endl;
		return false;
	}
	cout << "���ӳɹ�" << endl;
	tcp->sendMsg(encstr);
	//�ȴ���������Ӧ
	string msg = tcp->recvMsg();

	//�������������� -> ����(�����л�)
	//
	factory = new RespondFactory(msg);
	c = factory->createCodec();
	RespondMsg* resData = (RespondMsg *)c->decodeMsg(); 
	/*
	void* RespondCodec::decodeMsg()
	{
		m_msg.ParseFromString(m_encstr);
		return &m_msg;
	}
	*/
	if (!resData->status())
	{
		cout << "��ԿЭ��ʧ��" << endl;
		return false;
	}
	string key = rsa.rsaPriKeyDecrypt(resData->data());
	cout << "�ԳƼ��ܵ���ԿΪ:" << key << endl;
	delete factory;
	delete c;
	//ά��һ��������
	tcp->disConnect();
	delete tcp;
	return true;
}

bool ClientOP::seckeyCheck()
{
	return false;
}

void ClientOP::seckeyZhuxiao()
{
}