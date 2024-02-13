#include <cstdio>
#include"ServerOP.h"
int main()
{
    ServerOP ser("server.json");
    ser.startServer();
    return 0;
}