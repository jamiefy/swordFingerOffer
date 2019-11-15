//
// Created by Administrator on 2019/11/15.
//
#include <iostream>
#include <stack>

std::stack<int> stack1;
std::stack<int> stack2;

void push(int node) {
    stack1.emplace(node);
}

//三种实现方法：1.先判断stack2是否为空再进行全部stack1弹出stack2压入操作
//2.在全部stack1弹出stack2压入操作后获取stack2栈顶值保存用于后续返回并弹出，之后再把stack2剩余值弹出压入到stack1
//3.stack1存数，stack2存地址
int pop() {
    int top= NULL;
    //先弹出已经进入stack2栈，在确保stack2为空的情况下再由stack1向stack2中输入
    if(!stack2.empty()){
        top=stack2.top();
        stack2.pop();
        return top;
    }
    while(!stack1.empty()){
        stack2.emplace(std::move(stack1.top()));
        stack1.pop();
    }
    if(!stack2.empty()){
        top=stack2.top();
        stack2.pop();
    }
    return top;
}

//if条件使用stack2.empty()比！stack2.empty()编码更简便且消耗更少空间
int popImp() {
    int top;
    //先弹出已经进入stack2栈，在确保stack2为空的情况下再由stack1向stack2中输入
    if(stack2.empty()){
        while(!stack1.empty()){
            stack2.emplace(std::move(stack1.top()));
            stack1.pop();
        }
    }
    if(!stack2.empty()){
        top=stack2.top();
        stack2.pop();
    }
    return top;
}

//数据和地址分开存储
int address=0;
int pushNumAddress(int node){
    stack1.push(node);
    stack2.push(address++);
}

int popNumAddress(){
    for(int i=0;i<stack2.size();i++){
        //if(stack2[i]!=-1)思路很好但是栈在c++中没有下标操作
    }
}