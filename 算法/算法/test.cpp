#include <bits/stdc++.h>
using namespace std;

class MyQueue {
public:
    MyQueue() {

    }
    
    void push(int x) {
        while(!MySta.empty()){
            MySta2.push(MySta.top());
            MySta.pop();
        }
        MySta2.push(x);
        while(!MySta2.empty()){
            MySta.push(MySta2.top());
            MySta2.pop();
        }
    }
    
    int pop() {
        while(!MySta.empty()){
            MySta2.push(MySta.top());
            MySta.pop();
        }
        int ans = MySta2.top();
        MySta2.pop();
        while(!MySta2.empty()){
            MySta.push(MySta2.top());
            MySta2.pop();
        }
        return ans;

    }
    
    int peek() {
        while(!MySta.empty()){
            MySta2.push(MySta.top());
            MySta.pop();
        }
        int ans = MySta2.top();
        while(!MySta2.empty()){
            MySta.push(MySta2.top());
            MySta2.pop();
        }
        return ans;
    }
    
    bool empty() {
        return MySta.empty();
    }

    int Size(){
        return MySta.size();
    }

    stack<int> MySta;
    stack<int> MySta2;
};

int main(){
    MyQueue que;
    que.push(1);
    que.push(2);

    cout<<que.peek()<<endl;
    cout<<que.pop()<<endl;
    cout<<que.Size()<<endl;
}