//
// Created by anranzhai on 2019/11/12.
//
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

//只能原地修改字符指针指向的字符数组，不能转为string之后再赋值,否则原字符数组不发生改变
//如果要将string直接转换成const char *类型。string有3个函数可以运用。一个是.c_str()，一个是data成员函数,一个是copy
//c_str是标准的做法，返回的char*一定指向一个合法的用'\0'终止的C兼容的字符串。
//所以，如果需要C兼容的字符串，c_str  是标准的做法，data 并不保证所有STL的实现的一致性,copy必须手动加上结束符
//char*转成string可以直接赋值，不过下面这种情况是会出现问题的。
// string s;
//char *p = "adghrtyh";
//s = p;
//有一种情况：当我们定义了一个string类型之后，用printf("%s",s1);输出是会出问题的。这是因为“%s”要求后面的对象的首地址。
//但是string不是这样的一个类型。所以肯定出错。用cout输出是没有问题的，若一定要printf输出。那么可以这样：printf("%s",s1.c_str())
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
    //需要保证str指向字符数组的空间足够大
    //strcpy(str,s.c_str());//正确：strcpy(char *_dest,const char *_str)给指针指向的内容赋值,内容改变，也可以使用*str对str所指向的字符数组循环赋值
    //str= const_cast<char*>(s.c_str());错误：给指针赋值是值传递对函数外的值没有改变（引用是地址传递会改变函数外的值），str最后指向的内容是垃圾，因为s.c_str指向的时临时指针，不能对其进行操作，s对象被析构，其内容被处理,只有 strcpy(str,s.c_str());这样处理才不会出错
    s.copy(str,s.size(),0);
    *(str+s.size())='\0';//一定要手动加上结束符
}

void replaceSpaceFind(char *str,int length) {
    std::string s=str;
    auto it=s.begin();
    //泛型算法中的find(迭代器begin,迭代器end,所要查找的元素)而不是在string容器中
    for(;(it=find(it,s.end(),' '))!=s.end();){//这里必须使用' '表示元素而不能使用“ ”表示的字符串，这点不同于string.find
        s.replace(it,it+1,"%20");
    }
    //需要保证str指向字符数组的空间足够大
    strcpy(str,s.c_str());//strcpy(char *_dest,const char *_str)给指针指向的内容赋值,内容改变，也可以使用*str对str所指向的字符数组循环赋值
    //str= const_cast<char*>(s.c_str());给指针赋值是值传递对函数外的值没有改变（引用是地址传递会改变函数外的值）
}

//从前往后替换，后面的字符要不断往后移动，要多次移动，所以效率低下
//从后往前，先计算需要多少空间，然后从后往前移动，则每个字符只为移动一次，这样效率更高一点
void replaceSpacePointer(char *str,int length) {
    int spaceNum=0;
    for(int i=0;i<length;i++){
        if(str[i]==' ')spaceNum++;
    }
    int newLength=length+spaceNum*2;
    char* ptr1=str+length;//ptr1指向原字符串结束符’/0‘
    //需要保证str指向字符数组的空间足够大
    char* ptr2=str+newLength;//ptr2指向新字符串应存放结束符的位置
    while(ptr1<ptr2){//当ptr1==ptr2时,从右到左最后一个空格已经替换成“%20”,循环可以停止
        if(*ptr1==' '){
            *ptr2--='0';
            *ptr2--='2';
            *ptr2--='%';
        } else{
            *ptr2--=*ptr1;
        }
        ptr1--;
    }
}

int main(){
    char c[100]=" helloworld";
    //不能使用string对象初始化char*,反之可以
    char *s=c;
    replaceSpaceFind(s,10);
    std::cout<<s;
}