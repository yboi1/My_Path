#include <iostream>
using namespace std;


template <typename T>
void InsertSort(T arr[], int n, int i){
    int tmp = arr[i], k;
    for(k = i-n; k>=0&&arr[k+n]<arr[k]; k -= n){
        arr[k+n] = arr[k];
    }
    arr[k+n] = tmp;
    
}

template<typename T>
void Sort(T *arr, int size){
    for(int n = size / 2 ; n > 0; n /=2 ){
        for(int i = n; i < size; i++){
            InsertSort(arr, n, i);  //i为起始位置   n为间距大小
        }

    }
}

template <typename T>
void print(T arr[], int size){
    for(int i = 0; i < size; i++){
        cout<<arr[i]<<" ";
    }
    cout <<endl;
}

int main()
{
    int arr[] = {10, 8, 5, 9, 4, 3, 1, 2};
    int size = sizeof(arr)/sizeof(arr[0]);
    Sort<int> (arr, size);
    print<int> (arr, size);


}