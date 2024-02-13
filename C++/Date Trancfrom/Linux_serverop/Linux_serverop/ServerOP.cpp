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
	//解析json文件，读文件->Value
	ifstream ifs(json);
	Value root;
	Reader r;
	r.parse(ifs, root);
	//读取客户端和服务器端口ID
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
		cout << "等待客户端连接..." << endl;
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
	//0.对签名进行校验 -> 公钥解密 -> 得到公钥 -
	//将收到的公钥数据写到本地磁盘
	ofstream ofs("public.pem");
	ofs << reqMsg->data();
	//创建非对称加密对象
	Cryptographic rsa("public.pem", false);

	//创建哈希对象
	Hash sha(T_SHA1);
	sha.addData(reqMsg->data());
	bool bl = rsa.rsaVerify(sha.result(),reqMsg->sign());//data为公钥,sign为签名
	RespondInfo info;
	if (bl == false)
	{
		cout << "签名校验失败..." << endl;
		info.status = false;
	}
	else
	{
		//1.生成随机字符串
		string key = this->getRandKey(Len16);
		//2.通过公钥加密
		string secKey = rsa.rsaPubKeyEncrypt(key);
		//3.初始化回复的数据
		info.clientID = reqMsg->clientid();
		info.data = secKey;
		info.seckeyID = 12;
		info.serverID = m_serverID;
		info.status = true;	
	}
	//4.序列化
	CodecFactory* fac = new RespondFactory(&info);
	Codec* c = fac->createCodec();
	string encMsg = c->encodeMsg();
	//5.发送数据
	return encMsg;

}

void* ServerOP::working(void* arg)
{
	sleep(1); //确保将tcp对象加入到map中
	string data = string();
	//通过参数将传递的this对象转换
	ServerOP* op = (ServerOP*)arg;
	//从op中将通信的套接字对象取出
	TcpSocket* tcp = op->m_tcp[pthread_self()];
	//1.接受客户端数据 -> 编码
	string msg = tcp->recvMsg();
	//2.反序列化 -> 得到原始数据
	CodecFactory* fac = new RequestFactory(msg);
	Codec* c = fac->createCodec();
	RequestMsg* req = (RequestMsg*)c->decodeMsg();
	//3.取出数据
	//判断客户端是什么请求
	switch (req->cmdtype())
	{
	case 1:
		//秘钥协商
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

	//释放资源
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
		case 3: //特殊字符
			RandStr.append(1, sp[rand() % strlen(sp)]);
			break;
		}
	}
	return string();
}
