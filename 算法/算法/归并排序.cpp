#include <bits/stdc++.h>
using namespace std;

void Mmerge(vector<int> &arr, int left, int mid, int right){
    int cL = mid-left+1;
    int cR = right-mid;
    vector<int> arrL(arr.begin()+left, arr.begin()+mid+1);
    vector<int> arrR(arr.begin()+mid+1, arr.begin()+right+1);
    int i = 0;

    for(i = left; cL&&cR ; i++){
            if(arrL[mid-cL]>arrR[right-cR]){
                arr[i] = arrL[mid-cL];
                cL--;
            }
            else{
                arr[i] = arrR[right-cR];
                cR--;
            }

        while(cL){
            arr[i++] = arr[i] = arrL[mid-cL];
            cL--;
        }
        while(cR){
            arr[i++] = arrR[right-cR];
            cR--;
        }
    }
}

void sortar(vector<int >&arr, int low, int high){
    if(low>=high)    return;
    int mid = (low+high)/2;
    sortar(arr, low, mid);
    sortar(arr, mid+1, high);
    Mmerge(arr, low, mid, high);
}


int main()
{
    vector<int > arr = {2,1,3,5,9,6,7,8,4};
    sortar(arr, 0, arr.size()-1);
    for(auto x : arr){
        cout<<x<<" ";
    }
    cout << endl;
}