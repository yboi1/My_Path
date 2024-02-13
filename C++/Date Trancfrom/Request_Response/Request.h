#pragma once
#include "Codec.h"
#include<string>
#include"RequestMsg.pb.h"
using namespace std;
struct RequestInfo
{
    int cmd;
    string clientID;
    string serverID;
    string sign;
    string data;
};
class Request :
    public Codec
{
public:
    Request();
    Request(string encstr);
    Request(RequestInfo* Meg);
    void initMessage(string encstr);
    void initMessage(RequestInfo* Meg);
    string encodeMsg();
    void* decodeMsg();
    ~Request();
private:
    string m_encStr;
    RequestMsg m_msg;
};

