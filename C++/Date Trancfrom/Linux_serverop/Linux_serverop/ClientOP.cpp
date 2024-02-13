#include"ClientOP.h"
#include<json.h>
#include<fstream>
#include<sstream>
#include"RequestCodec.h"
#include"RequestFactory.h"
#include"RsaCrypto.h"
#include"TcpSocket.h"
#include"RespondFactory.h"
#include"RespondCodec.h"
using namespace Json;
using namespace std;
ClientOP::ClientOP(string jsonFile)
{
	//解析json文件，读文件->Value
	ifstream ifs(jsonFile);
	Value root;
	Reader r;
	r.parse(ifs, root);
	//读取客户端和服务器端口ID
	m_info.clientId = root["ClientId"].asString();
	m_info.serverId = root["ServerId"].asString();
	m_info.ip = root["ip"].asString();
	m_info.port = root["port"].asInt();

}
bool ClientOP::seckeyAgree()
{
	//0.生成秘钥对，将公钥字符串读出
	Cryptographic rsa;
	//生成秘钥对
	rsa.generateRsakey(1024);
	//读公钥文件
	ifstream ifs("public.pem");
	stringstream str;
	str << ifs.rdbuf();
	//初始化系列化数据
	RequestInfo reqInfo;
	reqInfo.clientID = m_info.clientId;
	reqInfo.serverID = m_info.serverId;
	reqInfo.cmd = 1;	//秘钥协商
	reqInfo.data = str.str();	//非对称加密的秘钥
	reqInfo.sign = rsa.rsaSign(str.str());	//签名
	CodecFactory* factory = new RequestFactory(&reqInfo);
	Codec* c = factory->createCodec();
	//得到序列化后的数据，可以将其发送给客户端
	string encstr = c->encodeMsg();		//编码后的数据
	//释放资源
	delete factory;
	delete c;

	//客户端连接服务器
	TcpSocket* tcp = new TcpSocket;
	//连接服务器，配置文件
	//connectToHost(string ip, unsigned short port, int timeout)
	tcp->connectToHost(m_info.ip, m_info.port);
	tcp->sendMsg(encstr);
	//等待服务器回应
	string msg = tcp->recvMsg();

	//解析服务器数据 -> 解码(反序列化)
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
		cout << "秘钥协商失败" << endl;
		return false;
	}
	string key = rsa.rsaPriKeyDecrypt(resData->data());
	cout << "对称加密的秘钥为:" << key << endl;
	delete factory;
	delete c;
	return true;
}
