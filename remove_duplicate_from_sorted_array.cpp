/*Q: 26 Remove Duplicates from Sorted Array

Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears 
only once. The relative order of the elements should be kept the same. Then return the number of unique elements in nums.

Consider the number of unique elements of nums to be k, to get accepted, you need to do the following things:
Change the array nums such that the first k elements of nums contain the unique elements in the order 
they were present in nums initially. The remaining elements of nums are not important as well as the size of nums.
Return k.
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution1 {
public:
    int removeDuplicates(vector<int>& nums) {
        int count = 1;//因為第一個數字本身就是特別的也不需修改
        for(int i = 1; i < (int)nums.size(); i++){
           if(nums[i] != nums[i-1]){
               nums[count] = nums[i];
               count++;
           }
        }
        for(int i = 0; i < count; i++)
           cout << nums[i] <<endl;
        cout << count;
        return count;
    }
};

//把他寫的更像雙指針
class Solution2 {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0;
        int fast = 1;
        for(fast; fast < nums.size(); fast++){
            if(nums[fast] != nums[slow]){
                slow++;
                // 维护 nums[0..slow] 无重复
                nums[slow] = nums[fast];
            }
        }
        //幾個元素為索引+1
        return slow+1;
    }
};

//la大寫法
class Solution3 {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0;
        int fast = 0;
        while(fast < nums.size()){
            if(nums[slow] != nums[fast]){
                slow++;
                // 维护 nums[0..slow] 无重复
                nums[slow] = nums[fast];
            }
            fast++;
        }
        //幾個元素為索引+1
        return slow+1;
    }
};

int main(){
    vector<int> nums;
    int x = 0;
    for(int i = 0 ; i < 10; i++){
        cin>>x;
        nums.push_back(x);
    }

    Solution1 v;
    v.removeDuplicates(nums);
}