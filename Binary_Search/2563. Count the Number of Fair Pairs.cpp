/*
2563. Count the Number of Fair Pairs
*/


// Two Pointer TC:O(nlgn) SC:O(1) 
class Solution {
    using LL = long long;
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(), nums.end());
        
        return helper(nums, upper) - helper(nums, lower-1);
    }
    LL helper(vector<int>& nums, int thr){
        LL res = 0;
        int n = nums.size();
        int j = n-1;
        for(int i = 0, j = n-1; i < j; i++){
            while(j > i && nums[j] + nums[i] > thr){
                j--;
            }
            res += (j-i);
        }

        return res;
    }
};

// Binary Search TC:O(nlgn) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        // Binary Search
        sort(nums.begin(), nums.end());
        //給定一個數字
        int n = nums.size();
        LL res =0;
        for(int i = 0; i < n; i++){
            auto iter1 = lower_bound(nums.begin(), nums.end(), lower-nums[i]);
            auto iter2 = upper_bound(nums.begin(), nums.end(), upper-nums[i]);
            if(iter1 == nums.end() || iter2 == nums.begin()) continue;
            iter2 = prev(iter2,1);
            
            if(*iter2 >= nums[i] && *iter1 <= nums[i]) res += (iter2 - iter1);
            else res += (iter2 - iter1+1);
        }

        return res/2;
    }
};

/*
找出一個數組中滿足 lower <= nums[i] + nums[j] <= upper 的對數量
想到兩個方法
1. two pointer 
2. binary search
1 2 3 4 5 6 upper = 6 lower = 4
ex : 3 6-3 4-3 之間 1~3之間的數字
lower - nums[i] <= nums[j] <= upper - nums[i]
此題考的比較細緻的地方在於
1. i j誰大誰小不管 得到的答案除以二
2. 有可能找到的位置包含了nums[i]本身 這種條件就要去掉 看你找的範圍是否把nums[i]包進去了
*/
