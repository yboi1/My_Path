#include<iostream>
#include<Json/Json.h>
#include<fstream>
using namespace std;
using namespace Json;
void Write()
{
	Value man;
	man.append(12);
	man.append(13.45);
	man.append("12138");
	man.append(true);
	man.append(false);
	Value woman;
	woman.append(1);
	woman.append(2);
	woman.append(3);
	man.append(woman);
	Value Cla;
	Cla["a"] = "b";
	man.append(Cla);
	FastWriter w;
	string str = w.write(man);
	ofstream ofs("Json.json");
	ofs << man;
}
void Read()
{
	ifstream obj("Json.json");
	Reader r;
	Value root;
	r.parse(obj, root);
	cout << root << endl;
}
int main()
{
	Write();
	Read();
}