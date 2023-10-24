/*
34. Find First and Last Position of Element in Sorted Array

Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
If target is not found in the array, return [-1, -1].
You must write an algorithm with O(log n) runtime complexity.

Example 1:
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Example 2:
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]

Example 3:
Input: nums = [], target = 0
Output: [-1,-1]
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//好多種寫法...先來寫最腳踏實地的binary search 吧 time o(lgn) space o(1)
class Solution1 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ans;
        int left = 0;
        int right = nums.size()-1;
        while(left < right){ //先求最左邊那項
            int mid = left + (right - left)/2;  //特別注意！這種寫法到最後ex 0,1 會選擇0 左邊的做為mid
            if(nums[mid] < target){
                left = mid+1;
            }
            else if(nums[mid] > target){
                right = mid-1;
            }
            else right = mid;
        }
        if(left == right && nums[left] == target){
            ans.push_back(left);
        }
        else ans.push_back(-1);
        
        left = 0;
        right = nums.size()-1;
        while(left < right){  //開始求最右邊那項
           int mid = left + (right -left+1)/2; //這裡要check 自己是要哪一項 如果沒改＋1會陷入無限迴圈喔
           if(nums[mid] < target){
            left = mid+1;
           }
           else if(nums[mid] > target){
            right = mid-1;
           }
           else left = mid; //直到left = right停止即找到 
        }
        if(left == right && nums[left] == target){
            ans.push_back(left);
        }
        else ans.push_back(-1);
        for(auto x:ans){
            cout << x << endl;
        }
        return ans;
    }
};

//善用c++ api lowerbound upperbound：（這兩個的時間複雜度為lgn) time o(lgn) space o(1)
class Solution2 {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ans;
        auto pos = lower_bound(nums.begin(), nums.end(), target);//去找大於或等於target的那個位置
        if(pos != nums.end() && *pos == target){
            ans.push_back(pos - nums.begin()); //相減可求出index
        }
        else ans.push_back(-1);

        pos = upper_bound(nums.begin(), nums.end(), target); //去找大於的那個位置
        pos = prev(pos, 1);
        if(pos != nums.begin() && *pos == target){
            ans.push_back(pos -nums.begin());
        }
        else ans.push_back(-1);

        for(auto x:ans){
            cout << x<< endl;
        }

        return ans;
    }
};

//最神的la 大解法 tc: o(lgn) sc: o(1)
class Solution {
// la大 概念來做
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = leftbound(nums, target);
        int right = rightbound(nums, target);
        return {left, right};
    }
    int leftbound(vector<int>& nums, int target){//找左側邊界
        int left = 0;
        int right = nums.size(); //左閉右開

        while(left < right){ //出去條件left = right
            int mid = left + (right - left) /2;
            if(nums[mid] == target){ 
                right = mid;
            }
            else if(nums[mid] < target){
                left = mid + 1;//左閉
            }
            else if(nums[mid] > target){
                right = mid; //右開
            }
        }
        //確認邊界
        if(left < 0 || left >= nums.size()) return -1;

        return nums[left] == target ? left:-1;
    }
    int rightbound(vector<int>& nums, int target){//找右側邊界
        int left = 0;
        int right = nums.size(); //左閉右開

        while(left < right){ //出去條件left = right
            int mid = left + (right - left)/2;

            if(nums[mid] == target) left = mid+1; //左閉
            else if(nums[mid] > target){
                right = mid;
            }
            else if(nums[mid] < target){
                left = mid+1;
            }
        }

        //判斷邊界條件
        if( left -1 < 0 || left-1 >= nums.size()) return -1;// left-1的原因是走到nums[mid] == target 時left mid會被加一

        return nums[left-1] == target ? left-1:-1;
    }

};

/*
解題思路
分成查找左側邊界跟右側邊界
*/


int main(){
    vector<int> nums = {5,7,7,8,8,10};
    int target = 8;
    Solution1 a;
    a.searchRange(nums, target);
    Solution2 b;
    b.searchRange(nums, target);    
}