#include "Response.h"
#include"RequestMsg.pb.h"
#include<iostream>
using namespace std;
/*
	message RequestMsg
{
    int32 cmdType = 1;
    bytes clientID = 2;
    bytes serverID = 3;
    bytes sign = 4;
    bytes data = 5;
}

message RespondMsg
{
    bool rv = 1;
    int32 seckeyid = 2;
    bytes clientID = 3;
    bytes serverID = 4;
    bytes data = 5;
}
*/
Response::Response()
{

}
Response::Response(string encstr)
{
	initMessage(encstr);
}
Response::Response(RespondInfo* Meg)
{
	initMessage(Meg);
}
void Response::initMessage(string encstr)
{
    m_encStr = encstr;
}
/*
    int32 status = 1;
    int32 seckeyID = 2;
    bytes clientID = 3;
    bytes serverID = 4;
    string data = 5;
*/
void Response::initMessage(RespondInfo* info)
{
    m_msg.set_status(info->status);
    m_msg.set_seckeyid(info->seckeyID);
    m_msg.set_clientid(info->clientID);
    m_msg.set_serverid(info->serverID);
    m_msg.set_data(info->data);

}
string Response::encodeMsg()
{
    string output;
    m_msg.SerializeToString(&output);
    return output;
}
void* Response::decodeMsg()
{
    m_msg.ParseFromString(m_encStr);
    return &m_msg;
}
Response::~Response()
{

}