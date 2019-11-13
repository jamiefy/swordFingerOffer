//
// Created by anranzhai on 2019/11/13.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

struct ListNode {
        int val;
        struct ListNode *next;
        ListNode(int x) :
             val(x), next(NULL) {
        }
};
//尾插法,然后逆序
std::vector<int> printListFromTailToHead(ListNode* head) {
    std::vector<int> vec;
    while(head!=nullptr){
        vec.emplace_back(head->val);
        head=head->next;
    }
    std::reverse(vec.begin(),vec.end());
    return vec;
}
//头插法
std::vector<int> printListFromTailToHeadHeadInsert(ListNode* head) {
    std::vector<int> vec;
    while(head!=nullptr){
        vec.emplace(vec.begin(),head->val);
        head=head->next;
    }

    return vec;
}
//利用栈的先进后出
std::vector<int> printListFromTailToHeadStack(ListNode* head) {
    std::vector<int> vec;
    std::stack<int> st;
    while(head!=nullptr){
        st.emplace(head->val);
        head=head->next;
    }
    while(!st.empty()){
        //加上move时间消耗和空间消耗都会减少
        vec.emplace_back(std::move(st.top()));
        st.pop();
    }
    return vec;
}
//以上三种方法时间复杂度和空间复杂度都是O(n)，执行过程中时间消耗和空间消耗和尾插法都不相上下，在加std::move的情况下栈的方法时间消耗和空间消耗最少
int main(){
    ListNode head(0), a(1),b(2);
    head.next=&a;
    a.next=&b;
    std::vector<int> vec=printListFromTailToHeadHeadInsert(&head);
    for(auto &i:vec){
        std::cout<<i<<" ";
    }
}