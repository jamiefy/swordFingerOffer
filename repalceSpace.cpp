//
// Created by anranzhai on 2019/11/12.
//
#include <iostream>
#include <string>

void replaceSpace(char *str,int length) {
    std::string s=str;
    size_t pos=0;
    while(pos<length){
        pos=s.find(" ",pos);
        if(pos>=length)break;
        else
            s.replace(pos,1,"%20");
        pos+=3;
        length+=3;
    }
    //没能实现把变换过的string值付给指针
    str= const_cast<char *>(s.c_str());
}


int main(){
    char *s="hello world and you";
    replaceSpace(s,19);
    std::cout<<s;
}