/*
2972. Count the Number of Incremovable Subarrays II
*/

// TC:O(n+ m*lgk) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long incremovableSubarrayCount(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), INT_MIN);
        nums.push_back(INT_MAX);
        //真正數字範圍從1~n
        int L = 1;
        while(L <= n){
            if(nums[L] < nums[L+1]) L++;
            else break;
        }

        int R = n;
        while(R >= 1){
            if(nums[R] > nums[R-1]) R--;
            else break;
        }

        if(R < L) return n*(n-1)/2 + n;

        LL res = 0;
        for(int i = 0; i <= L; i++){
            auto iter = upper_bound(nums.begin()+R, nums.end(), nums[i]);
            res += (nums.end() - iter);
        }

        return res;
    }
};
