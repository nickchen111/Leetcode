/*
268. Missing Number
*/

#include <iostream>
#include <vector>
#include <numeric> //定義accumulate
using namespace std;


//binary search TC: o(lgn+nlgn)因為有sort SC: o(1)
class Solution1 {
public:
    int missingNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int low = 0;
        int high = nums.size();
        int mid = 0;
        while(low < high){
            mid = (low + high)/2;
            if(nums[mid] > mid){
                high = mid; //代表我要的index不可能超過mid 所以high =mid
            }
            else low = mid + 1; //代表目前都算合理 要return的是low 所以low +1看是否為正確的位置
        }
        return low;
        
    }
};


//XOR 抑或 Bit- Manipulation TC: o(n) SC: o(1)
// 利用xor特性 0^0 = 0 / b^b = 0/ 0^a = a  / a^ b^ b = a
class Solution2 {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int x = 0; // i少的0在這呢～
        for(int i = 1; i <= n; i++){
            x = x^i^nums[i-1];  // nums[0~8] i: 1~ 9
        }
        return x;
    }
};

//利用數學公式 TC: o(n) SC:o(1)
class Solution3 {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        return (0 + n)*(n+1) /2 - accumulate(nums.begin(), nums.end(), 0);
    }
};

//indexing sort TC: o(n) SC:o(1)
class Solution {
    //indexing sort
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        nums.push_back(n+1);//隨便一個不可能出現的數字

        for(int i = 0; i<n; i++){
            while(nums[i] != i && nums[i]<=n && nums[i] != nums[nums[i]]){
                swap(nums[i], nums[nums[i]]);
            }
        }
        
        for(int i = 0; i<=n; i++){
            if(nums[i] != i) return i;
        }

        return -1;
    }
};

