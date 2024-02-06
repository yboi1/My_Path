#include <bits/stdc++.h>
using namespace std;

void swapar(vector<int> &arr, int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void bigHeapBuild(vector<int> &arr, int len, int root){
    int largest = root;
    int left = 2*root + 1;
    int right = 2*root + 2;
    if(left<len && arr[left]>arr[largest])   largest = left;
    if(right<len && arr[right]>arr[largest])   largest = right;

    if(largest!=root){   
        swapar(arr, largest, root);
        bigHeapBuild(arr, len, largest);
    }

}

void sortHeap(vector<int> &arr){
    for(int i = (arr.size()/2)-1; i >= 0; i-- ){
        bigHeapBuild(arr, arr.size(), i);
    }
    for(int i = arr.size()-1; i >= 0; i--){
        swapar(arr, 0, i);
        bigHeapBuild(arr, i, 0);
    }

}

vector<int> sortArray(vector<int> arr){
    sortHeap(arr);
    return arr;
}


int main(){
    vector<int> arr = {1,3,2,5,9,4,6,7,8};
    sortHeap(arr);
    for(auto x:arr) cout<<x;
    cout<<endl;
}