//
// Created by anranzhai on 2019/11/13.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//递归 泛型算法 迭代器
TreeNode* reConstructBinaryTree(std::vector<int> pre,std::vector<int> vin) {
    if(pre.size()==0 || vin.size()==0)
        return nullptr;
    //构造节点指针，且分配空间
    TreeNode* node=new TreeNode(pre[0]);
    auto it=find(vin.begin(),vin.end(),pre[0]);
    int middle=it-vin.begin();
    std::vector<int> leftTreePre(pre.begin()+1,pre.begin()+middle+1);
    std::vector<int> leftTreeVin(vin.begin(),it);
    node->left=reConstructBinaryTree(leftTreePre,leftTreeVin);
    std::vector<int> rightTreePre(pre.begin()+middle+1,pre.end());
    std::vector<int> rightTreeVin(it+1,vin.end());
    node->right=reConstructBinaryTree(rightTreePre,rightTreeVin);
    return node;
}

//递归 引用传递 值传递
TreeNode* reConstruct(std::vector<int> &pre,std::vector<int> &vin,int leftPreStart,int leftPreEnd,int rightVinStart,int rightVinEnd){
    if(leftPreStart>leftPreEnd || rightVinStart>rightVinEnd){
        return nullptr;
    }

    //std::shared_ptr<TreeNode> node=std::shared_ptr<TreeNode>(new TreeNode(pre[leftPreStart]));会出现指针异常：不能采用智能指针，智能指针会自动析构，无法找到原来的地址内容
    TreeNode* node=new TreeNode(pre[leftPreStart]);
    int middle;
    for(int i=0;i<vin.size();i++){
        if(vin[i]==pre[leftPreStart]){
            middle=i;
            break;
        }
    }
//    auto it=find(vin.begin(),vin.end(),pre[leftPreStart]);
//    int middle=it-vin.begin()-rightVinStart;
    node->left=reConstruct(pre,vin,leftPreStart+1,leftPreStart+middle,rightVinStart,rightVinStart+middle-1);
    node->right=reConstruct(pre,vin,leftPreStart+middle+1,leftPreEnd,rightVinStart+middle+1,rightVinEnd);
    return node;
}

TreeNode* reConstructBinaryTreeReference(std::vector<int> pre,std::vector<int> vin) {
    if(pre.size()==0 || vin.size()==0)
        return nullptr;
    return reConstruct(pre,vin,0,pre.size()-1,0,vin.size()-1);
}


int main(){
    TreeNode* head=reConstructBinaryTree(std::vector<int>{1,2,4,7,3,5,6,8},std::vector<int>{4,7,2,1,5,3,8,6});
    std::cout<<head->val;
}