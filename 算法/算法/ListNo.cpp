#include <bits/stdc++.h>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* yummy = new ListNode();
        yummy->next = list1;
        ListNode* cur = yummy;
        int count = 0;
        while(count!=a){
            cur = cur->next;
            count++;
        }
        cur = cur->next;
        for(int i = 0; i < b-a+1; i++){
            ListNode* del = cur;
            cur = cur->next;
            delete(del);
        }
        ListNode* l2 = new ListNode();
        l2->next = list2;
        while(l2->next != NULL){
            l2 = l2->next;
        }
        l2->next = cur;
        return yummy->next;

    }
int main(){
    ListNode* l1 = new ListNode(3);
    ListNode* l2 = new ListNode(3);
    ListNode* l3 = new ListNode(3);
    ListNode* l4 = new ListNode(3);
    ListNode* l5 = new ListNode(3);
    l1->next = l2;
    l2->next = l3;
    
    l4->next = l5;

    ListNode*tmp = mergeInBetween(l1, 1, 2, l4);
    // while(tmp->next!=NULL){  cout<<tmp->val<<"->"; tmp=tmp->next;}
    // cout<<tmp->next<<endl;
}