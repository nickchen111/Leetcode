/*
2163. Minimum Difference in Sums After Removal of Elements
*/


// TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long minimumDifference(vector<int>& nums) {
        int n = nums.size();
       
        vector<LL> suffix(n);
        priority_queue<LL, vector<LL>, greater<>> mx;
        LL sum = 0;
        for(int i = n-1; i >= 2*n/3; i--) {
            mx.push(nums[i]);
            sum += (LL) nums[i];
        }

        suffix[2*n/3] = sum;
        for(int i = 2*n/3-1; i >= n/3; i--) {
            if(nums[i] > mx.top()) {
                sum -= mx.top();
                mx.pop();
                mx.push(nums[i]);
                sum += (LL)nums[i];
            }
            suffix[i] = sum;
        }

        LL prefix = 0;
        priority_queue<LL, vector<LL>, less<>> mn;
        for(int i = 0; i < n/3; i++) {
            mn.push(nums[i]);
            prefix += (LL)nums[i];
        }

        LL res = prefix - suffix[n/3];
        for(int i = n/3; i < 2*n/3; i++) {
            if(nums[i] < mn.top()){
                prefix -= mn.top();
                mn .pop();
                prefix += (LL)nums[i];
                mn.push(nums[i]);
            }

            res = min(res, prefix - suffix[i+1]);
        }

        return res;
    }
};

/*
可以移除n/3個數字 移除後的前面一半的sum - 後面一半的sum 要最小
前面盡量小 後面要大
*/
