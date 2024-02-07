#include <bits/stdc++.h>
#include "TuTorialConfig.h"
using namespace std;

int main(int argc, char*argv[]){
    if(argc < 2){
        // cout<<"usage: "<<argv[0]<<endl;
        // return 1;
        // 打印版本
        cout<<argv[0]<<" Version "<< Tutorial_VERSION_MAJOR << "."
            <<Tutorial_VERSION_MINOR << endl;
        cout<<"Usage: "<<argv[0]" number "<<endl;
        return 1;
    }

    const double inputValue = stod(argv[1]);

    const double outputValue = sqrt(inputValue);

    cout<<"thr qeuart root of "<<inputValue<<
    " is " << outputValue<<endl;
    return 0;
}