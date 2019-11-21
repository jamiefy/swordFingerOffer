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

//
int minNumberInRotateArrayBinarySort(std::vector<int> rotateArray){
    if (rotateArray.empty())
        return 0;
    unsigned int first = 0, last = rotateArray.size() - 1;
    unsigned int mid;
    while (rotateArray[first] >= rotateArray[last]) {
        //当数组个数减到2个数时进入判断处理
        if (last - first == 1) {
            //middle=旋转位
            mid = last;//2个数时取最后位此时返回mid=last=first+1，最后从这里结束循环
            break;
        }
        //数组1个数或者3个数及以上
        mid = first + (last - first) / 2;
        //数组1个数时进入该判断处理,最后从这里结束循环
        if (rotateArray[first] == rotateArray[mid] && rotateArray[mid] == rotateArray[last])
            return [&]() -> int {
                int minVal = rotateArray[first];
                for (int i = first; i <= last; ++i)
                    minVal = std::min(minVal, rotateArray[i]);
                return minVal;
            }();
        //数组3个数及以上的时候进入下面两个if判断处理，处理完之后均能继续循环
        if (rotateArray[first] <= rotateArray[mid])//操作后first=mid满足rotateArray[first] <= rotateArray[mid]，则first位肯定不是数组的最小值，肯定能继续循环
            first = mid;
        else if (rotateArray[mid] <= rotateArray[last])//rotateArray[mid]<=rotateArray[last]时区间向左缩，说明旋转位在包括mid的左侧区间，缩小之后肯定能进入循环，如果是1个数则进1个数的if判断处理，如果是2个数则返回
            //mid=last=first+1，如果是3个数及以上则区间需要左移或者右移，假设现在处于极限条件：旋转位在左缩之后处于最右侧位，则区间需要不断右缩至2个数然后返回last=mid+1,所以最终返回值下标均为first
            last = mid;//不能使用last=mid-1，若使用可能漏掉最小值
//        if (rotateArray[first] >= rotateArray[mid])//错误
//            last=mid;
//        else if(rotateArray[mid]>=rotateArray[last])//错诶
//            first=mid;
    }
    return rotateArray[mid];//rotateArray[first+1]时可直接把mid=last步骤删去
}

int minNumberInRotateArrayBinarySortIMP(std::vector<int> rotateArray){
    if (rotateArray.empty())
        return 0;
    unsigned int first = 0, last = rotateArray.size() - 1;
    unsigned int mid;
    while (rotateArray[first] >= rotateArray[last]) {//rotateArray[first]>=rotateArray[last]时总能进入while处理，一旦rotateArray[first]<rotateArray[last]则跳出循环说明此时最小位置是first
        mid = first + (last - first) / 2;
        //数组1个数时进入该判断处理
        if (rotateArray[first] == rotateArray[mid] && rotateArray[mid] == rotateArray[last])
            return [&]() -> int {
                int minVal = rotateArray[first];
                for (int i = first; i <= last; ++i)
                    minVal = std::min(minVal, rotateArray[i]);
                return minVal;
            }();
        //数组2个数及以上的时候进入下面两个if判断处理，处理完之后均能继续循环
        if (rotateArray[first] <= rotateArray[mid])
            first = mid+1;//当满足rotateArray[first] <= rotateArray[mid]条件时，mid位置不可能是最小值，肯定能继续循环，所以直接对mid+1进行判断（当数组中包含2个数时mid=first,则first=mid+1=last，区间缩至1个数下一步循环进入1个数的判断处理并结束循环
        else if (rotateArray[mid] <= rotateArray[last])//rotateArray[mid]<=rotateArray[last]时区间向左缩，说明旋转位在包括mid的左侧区间，缩小之后肯定能进入循环，如果是1个数则进1个数的if判断处理，如果是2个数则返回last=mid+1，如果是3个数及以上
            //则区间需要左移或者右移，假设现在处于极限条件：旋转位在左缩之后处于最右侧位，则区间需要不断右缩至2个数然后返回last=mid+1,所以最终返回值下标均为first
            last = mid;//不能使用last=mid-1，若使用可能漏掉最小值
    }
    return rotateArray[first];
}

int main() {
    std::cout << minNumberInRotateArrayBinarySort(std::vector<int>({6501,6828,6963,7036,7422,7674,8146,8468,8704,8717,9170,9359,9719,9895,9896,9913,9962,154,293,334,492,1323,1479,1539,1727,1870,1943,2383,2392,2996,3282,3812,3903,4465,4605,4665,4772,4828,5142,5437,5448,5668,5706,5725,6300,6335}));
}