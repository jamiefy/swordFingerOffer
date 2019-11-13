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


TreeNode* reConstructBinaryTree(std::vector<int> pre,std::vector<int> vin) {
    if(pre.size()==0 || vin.size()==0)
        return nullptr;
    TreeNode* node=new TreeNode(pre[0]);
    auto it=find(vin.begin(),vin.end(),pre[0]);
    int leftTreeLength=it-vin.begin();
    std::vector<int> leftTreePre(pre.begin()+1,pre.begin()+leftTreeLength+1);
    std::vector<int> leftTreeVin(vin.begin(),it);
    node->left=reConstructBinaryTree(leftTreePre,leftTreeVin);
    int rightTreeLength=vin.end()-it-1;
    std::vector<int> rightTreePre(pre.begin()+rightTreeLength,pre.end());
    std::vector<int> rightTreeVin(it+1,vin.end());
    node->right=reConstructBinaryTree(rightTreePre,rightTreeVin);
    return node;
}

//智能指针更安全
TreeNode* reConstructBinaryTreeShared(std::vector<int> pre,std::vector<int> vin) {
    if(pre.size()==0 || vin.size()==0)
        return nullptr;
    std::shared_ptr<TreeNode> node=std::make_shared<TreeNode>(pre[0]);
    auto it=find(vin.begin(),vin.end(),pre[0]);
    int leftTreeLength=it-vin.begin();
    std::vector<int> leftTreePre(pre.begin()+1,pre.begin()+leftTreeLength+1);
    std::vector<int> leftTreeVin(vin.begin(),it);
    node->left=reConstructBinaryTree(leftTreePre,leftTreeVin);
    int rightTreeLength=vin.end()-it-1;
    std::vector<int> rightTreePre(pre.begin()+rightTreeLength,pre.end());
    std::vector<int> rightTreeVin(it+1,vin.end());
    node->right=reConstructBinaryTree(rightTreePre,rightTreeVin);
    return node.get();
}

int main(){
    TreeNode* head=reConstructBinaryTreeShared(std::vector<int>{1,2,4,7,3,5,6,8},std::vector<int>{4,7,2,1,5,3,8,6});
    std::cout<<head->val;
}