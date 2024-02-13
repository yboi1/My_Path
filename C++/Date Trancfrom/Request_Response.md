```c++
#include<iostream>
#include<string>
#include<stdlib.h>
#include"Codec.h" //基类
#include"Request.h"
#include"RequestMsg.pb.h"	
#include"Response.h"
using namespace std;
int main()
{
	RequestInfo reqInfo; //定义一个结构体方便传参
	reqInfo.cmd = 9;
	reqInfo.clientID = "OnePiece";
	reqInfo.serverID = "Luffy";
	reqInfo.data = "我要称为海贼王的男人";
	reqInfo.sign = "hhhh";
	Request req(&reqInfo);//调用Request的构造函数

    //先编码再解码
	string reqmsg = req.encodeMsg();
	Request req1(reqmsg);
	RequestMsg* reqMsg = (RequestMsg*)req1.decodeMsg();
    
    
	cout << "cmdtype: " << reqMsg->cmdtype()
		<< ", clientID: " << reqMsg->clientid()
		<< ", serverID: " << reqMsg->serverid()
		<< ", data: " << reqMsg->data()
		<< ", sign: " << reqMsg->sign() << endl;

	//*******************************************************
	/*
	struct RespondInfo
{
    int status;
    int seckeyID;
    string serverID;
    string clientID;
    string data;
};
	*/
	RespondInfo repInfo2;
	repInfo2.status = false;
	repInfo2.seckeyID = 10;
	repInfo2.serverID = "你好";
	repInfo2.clientID = "世界";
	repInfo2.data = "888";

	Response repMsg(&repInfo2);
	string repStr = repMsg.encodeMsg();

	Response repCev(repStr);
	RespondMsg* rep = (RespondMsg*)repCev.decodeMsg();
	cout << "status: " << rep->status()
		<< ", seckeyid: " << rep->seckeyid()
		<< ", serverid: " << rep->serverid()
		<< ", clientid: " << rep->clientid()
		<< ", data: " << rep->data() << endl;

	/*
	Request req(&reqInfo);

	string reqmsg = req.encodeMsg();
	Request req1(reqmsg);
	RequestMsg* reqMsg = (RequestMsg*)req1.decodeMsg();
	*/
	return 0;
}
```

