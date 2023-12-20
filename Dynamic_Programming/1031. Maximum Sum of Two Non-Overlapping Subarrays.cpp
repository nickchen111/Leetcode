/*
1031. Maximum Sum of Two Non-Overlapping Subarrays
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        
        return max(helper(nums,firstLen,secondLen), helper(nums,secondLen, firstLen));
    }

    int helper(vector<int>& nums, int x, int y){
        int n = nums.size();
        vector<int> dp1(n,0); //在 i以前最大的總和是多少
        vector<int> dp2(n,0); // 在 i 以後最大的總和是多少

        int sum = 0;
        for(int i = 0;  i < n; i++){
            if(i < x){
                sum += nums[i];
                dp1[i] = sum;
            }
            else {
                sum = sum + nums[i] - nums[i-x];
                dp1[i] = max(dp1[i-1], sum);
            }
        }
        
        sum = 0;
        for(int i = n-1;  i >= 0; i--){
            if(i + y > n - 1){
                sum += nums[i];
                dp2[i] = sum;
            }
            else {
                sum = sum + nums[i] - nums[i+y];
                dp2[i] = max(dp2[i+1], sum);
            }
        }
        
        int res = 0;
        for(int i = x-1; i < n-y; i++){
            res = max(res, dp1[i] + dp2[i+1]);
        }

        return res;
    }
};

/*
此題限定兩個長度 問說這兩個長度各取一個subarray 但不能重疊 問總和最多可以多少
我的想法是既然不知道len大的策略好還是len小的好 那就兩個都試一次
*/
