/*
3107. Minimum Operations to Make Median of Array Equal to K
*/

// TC:O(nlgn) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long minOperationsToMakeMedianK(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int mid = n/2;
        
        LL res = 0;
        int median = nums[mid];
        if(median == k) return res;
        else if(median < k){
            for(int i = mid+1; i < n; i++){
                if(nums[i] < k){
                    res += (k - nums[i]);
                }
            }
            res += (k - median);

            return res;
        }
        else {
            res += (median - k);
            for(int i = mid-1; i >= 0; i--){
                if(nums[i] > k){
                    res += (nums[i] - k);
                }
            }

            return res;
        }
        
       
    }
};


/*
先判斷是偶數個奇數個
偶數還要判斷要選哪個
中位數 比k大 要加到k並且不能比下一個大
這題詭異的地方在於中位數偶數狀況要優先選後面一位
*/
