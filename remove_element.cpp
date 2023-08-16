/*
Q:27 remove element

Given an integer array nums and an integer val, remove all occurrences of val in nums in-place. 
The order of the elements may be changed. Then return the number of elements in nums which are not equal to val.
Consider the number of elements in nums which are not equal to val be k, to get accepted, 
you need to do the following things:
Change the array nums such that the first k elements of nums contain the elements 
which are not equal to val. The remaining elements of nums are not important as well as the size of nums.
Return k.
*/
 
//這題如果單純是想解出裡面有幾個element不是val的值就很簡單 但是如果要去真正的將裡面的數值刪掉就有點詭異..
//解題思路為去count有幾個element 不屬於定義要刪除的值 計數回傳即可

#include <iostream>
#include <vector>
using namespace std;

class Solution1 {
public:
    int removeElement(vector<int>& nums, int val) {
        int index = 0;
        for(int i = 0; i < (int)nums.size(); i++){
             if(nums[i] != val){
                nums[index] = nums[i];
                index++;
             }
    }

    //也可以只print index範圍內的值呀呵呵
    int i = ((int)nums.size()) - index; //用總共幾個元素的數量去減掉index真正該有的數量就是要pop的次數
        for(;i > 0; i--){    
            nums.pop_back();
    }

    cout<< index<<endl;
    return index;
    }  
};

//原地刪除問題 用雙指針解吧 tc: o(n) sc: o(1)
class Solution2 {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        int fast = 0;
        while(fast < nums.size()){
            if(nums[fast] != val){
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        //返回長度 這裡是先給slow賦值在++ 所以不用＋1
        return slow;
    }
};

/*
解題思路 
用雙指針 fast 指導跟val 不一樣的值 就將slow等於fast 
解法更直觀
*/

int main(){
    int val = 3;
    vector<int> nums;
    int x = 0;
    for(int i = 0; i < 6; i++){
      cin >> x;
      nums.push_back(x);
    }

    Solution1 v;
    v.removeElement(nums, val);
    for(int i = 0; i< (int)nums.size(); i++ )
      cout<< nums[i];
    cout<<"\n"<<nums.size();
}