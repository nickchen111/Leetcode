/*
209. Minimum Size Subarray Sum
Given an array of positive integers nums and a positive integer target, return the minimal length of a subarray
whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.

Example 1:
Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Example 2:
Input: target = 4, nums = [1,4,4]
Output: 1

Example 3:
Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0
*/



#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        int sum = 0;
        int res = numeric_limits<int>::max();
        for(int i = 0; i < n; i++){
            sum += nums[i];
            while(left <= i && sum >= target){
                res = min(res, i-left+1); //判斷元素有多少個
                sum -=nums[left];
                left++;
            }
        }
        return res == numeric_limits<int>::max() ? 0:res;
    }
};


int main(){
    vector<int> nums = {2,3,1,2,4,3};
    int target = 7;
    Solution a;
    cout<< a.minSubArrayLen(target, nums);
}
