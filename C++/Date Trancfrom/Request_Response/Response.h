#pragma once
#include "Codec.h"
#include<string>
#include"RequestMsg.pb.h"
using namespace std;
struct RespondInfo
{
    int status;
    int seckeyID;
    string serverID;
    string clientID;
    string data;
};
class Response :
    public Codec
{
public:
    Response();
    Response(string encstr);
    Response(RespondInfo* Meg);
    void initMessage(string encstr);
    void initMessage(RespondInfo* Meg);
    string encodeMsg();
    void* decodeMsg();
    ~Response();
private:
    string m_encStr;
    RespondMsg m_msg;
};
