#include<iostream>
#include<string>
#include"ClientOP.h"
using namespace std;
int usage();
int main()
{
	ClientOP Clp("client.json");
	while (1)
	{
		int sel = usage();
		switch (sel)
		{
		case 1:
			//秘钥协商
			Clp.seckeyAgree();
			break;
		case 2:
			//秘钥校验
			Clp.seckeyCheck();
			break;
		case 3:
			//秘钥注销
			Clp.seckeyZhuxiao();
			break;
		}
	}
}

int usage()
{
	int nSel = -1;
	printf("\n  /*********************************************");
	printf("\n  /*********************************************");
	printf("\n  /***************1.秘钥协商                     ");
	printf("\n  /***************2.秘钥校验                     ");
	printf("\n  /***************3.秘钥注销                     ");
	printf("\n  /***************4.秘钥查看                     ");
	printf("\n  /***************0.退出系统                     ");
	printf("\n  /*********************************************");
	printf("\n  /*********************************************");
	printf("\n\n  选择：");

	scanf("%d", &nSel);
	while (getchar() != '\n');

	return nSel;
}