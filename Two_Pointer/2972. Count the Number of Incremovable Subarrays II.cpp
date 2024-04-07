/*
2972. Count the Number of Incremovable Subarrays II
*/

// TC: Two Pointer O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long incremovableSubarrayCount(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), INT_MIN);
        nums.push_back(INT_MAX);

        int L = 1;
        while(L <= n){
            if(nums[L] < nums[L+1]) L+=1;
            else break;
        }
        int R = n;
        while(R >= 1){
            if(nums[R] > nums[R-1]) R--;
            else break;
        }

        if(R < L) return n*(n-1)/2 + n; // 整段都遞增
        LL res = 0;
        int j = R;
        for(int i = 0; i <= L; i++){
            while(j <= n+1 && nums[i] >= nums[j]){
                j++;
            }
            // x x x n
            res += (n+2-j);
        }

        return res;

    }
};


// Binary Search TC:O(n+ m*lgk) SC:O(1)
