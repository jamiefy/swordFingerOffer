//
// Created by Administrator on 2019/11/15.
//
#include <iostream>
#include <vector>
#include <algorithm>

//时间复杂度：O(logn) 空间复杂度：O(1)
int minNumberInRotateArray(std::vector<int> rotateArray) {
    //size为0时返回0
    if(rotateArray.size()==0)
        return 0;
    int low=0,high=rotateArray.size()-1;
    //二分查找，不同于查找目标值的是：每个值都要遍历到且数组中肯定存在最小值，所以不能使用low<high只能使用low<=high也就是只能使用闭区间
    while(low<=high){
        int middle=low+(high-low)/2;
        //如果high-low=1或者high=low也就是在两个或一个数的范围内查找，可能存在middle-1<low或者middle+1>high的情况，此时进行else内的判断可能发生数组越界
        if(middle-1<low || middle+1>high){
            if(high-low==1)return rotateArray[low]>rotateArray[high]?rotateArray[high]:rotateArray[low];
            else if(high==low)return rotateArray[low];
        }else{//在三个或三个数以上的范围内查找，首先判断当前middle位的数值左右是否存在相等的值，找出不等于middle位数值的左右边界
            int left=middle-1,right=middle+1;
            //当left超出下限low时，停止循环
            while(left>=low){
                //当与middle位数值相等时，left左移，否则停止循环（跳出循环时left位数值不等于middle位的数值）
                if(rotateArray[left]==rotateArray[middle])left--;
                else break;
            }
            //当right超出上限high时，停止循环
            while(right<=high){
                //当与middle位数值相等时，right右移，否则停止循环（跳出循环时right位数值不等于middle位数值）
                if(rotateArray[right]==rotateArray[middle])right++;
                else break;
            }
            //如果left超出下限low且right超出上限high，说明整个数组全是middle位数值，数组最小值也就是取数组中任意值均可
            if(left<low && right>high)return rotateArray[low];
            //如果left超出下限low且right<=high，那把下限low改成等于middle位数值的所有数据的右边界，然后进行新一轮的二分查找，查找闭区间必须包括一个middle位数值不然就会把middle位数值漏掉
            else if(left<low)low=right-1;
            //如果right超出上限high且left>=low，那把上限high改成等于middle位数值所有数据的左边界，然后进行新一轮的二分查找，查找闭区间必须包括一个middle位数值不然就会把middle位数值漏掉
            else if(right>high)high=left+1;
            //如果left和right均在low和high的范围内，则比较middle位数值和left、right位数值的大小
            else{
                //当middle位数值左边第一个不等于它的值大于它且右边第一个不等于它的值大于它时，该middle位数值就是旋转部分的第一个数值，也就是整个数组最小的值
                if(rotateArray[left]>rotateArray[middle]&&rotateArray[middle]<rotateArray[right])return rotateArray[middle];
                //当middle位数值左边第一个不等于它的值小于它且右边第一个不等于它的值小于它时，该middle位数值就是旋转部分之前的第一个数值，也就是整个数组最大的值，它的后一位就是旋转部分的第一个数值，也就是整个数组最小的值
                else if(rotateArray[left]<rotateArray[middle]&&rotateArray[middle]>rotateArray[right])return rotateArray[right];
                //当middle位数值左边第一个不等于它的值小于它且右边第一个不等于它的值大于它时，说明middle不处于旋转交界处，要判断旋转位在middle的左边还是右边
                else{
                    //旋转位在middle的左边，high左移到最近的一个有效值（因为已经遍历过middle所以此时取值可除去middle）
                    if(rotateArray[middle]<rotateArray[high])high=left;
                    //旋转位在middle的右边，low右移到最近的一个有效值（因为已经遍历过middle所以此时取值可除去middle）
                    else if(rotateArray[middle]>rotateArray[high])low=right;
                }
            }
        }
    }
}

//时间复杂度：O(nlogn)
int minNumberInRotateArraySort(std::vector<int> rotateArray){
    std::sort(rotateArray.begin(),rotateArray.end());
    return rotateArray[0];
}

int main() {
    std::cout << minNumberInRotateArray(std::vector<int>({2, 3, 4, 5, 1, 1, 1, 1,1,1}));
}