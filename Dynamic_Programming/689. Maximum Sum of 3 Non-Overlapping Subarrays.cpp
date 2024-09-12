/*
689. Maximum Sum of 3 Non-Overlapping Subarrays
*/


// Three Pass + Slide Window TC:O(n) SC:O(4*n)
class Solution {
    using LL = long long;
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<LL> leftMax(n, LLONG_MIN/2);
        vector<LL> rightMax(n, LLONG_MIN/2);
        vector<int> leftIdx(n);
        vector<int> rightIdx(n);
        int idx = 0;
        LL sum = 0;
        LL maxVal = 0;
        for(int i = 0; i < n; i++){
            if(i < k-1){
                sum += (LL)nums[i];
            }
            else {
                sum += (LL)nums[i];
                if(sum > maxVal){
                    idx = i-k+1;
                    maxVal = sum;
                }
                leftMax[i] = maxVal;
                leftIdx[i] = idx;
                sum -= nums[i-k+1];
            }
        }

        // x x x x x k = 2
        maxVal = 0;
        sum = 0;
        for(int i = n-1; i >= 0; i--){
            if(i >= n-k+1){
                sum += (LL)nums[i];
            }
            else {
                sum += nums[i];
                if(sum >= maxVal){
                    idx = i;
                    maxVal = sum;
                }
                rightMax[i] = maxVal;
                rightIdx[i] = idx;
                sum -= nums[i+k-1];
            }
        }
        int idx1 = 0;
        int idx2 = 0;
        int idx3 = 0;
        maxVal = 0;
        // x x x x x x k = 2
        sum = 0;
        int i = k;
        for(int j = k; j < n-k; j++){
            sum += (LL)nums[j];
            if(j-i+1 == k){
                if(maxVal < sum + leftMax[i-1] + rightMax[j+1]){
                    maxVal = leftMax[i-1] + rightMax[j+1] + sum;
                    idx1 = leftIdx[i-1];
                    idx2 = i;
                    idx3 = rightIdx[j+1];
                }
                sum -= nums[i];
                i++;
            }
        }

        return {idx1, idx2, idx3};
    }
};

// DP TC:O(n) SC:O(9*n)
class Solution {
    using LL = long long;
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int presum[n+1];
        
        int memo[n+1][4];  // 初始化 memo
        nums.insert(nums.begin(), 0);  // 插入 0 保持 1-indexed
        for(int i = 1; i <= n; i++){
            presum[i] = presum[i-1] + nums[i];
        }
        int dp[n+1][4];
        LL maxVal = 0;
        int idx = 0;

        for(int i = k; i <= n-k; i++){
            if(maxVal < presum[i] - presum[i-k]){
                maxVal = presum[i] - presum[i-k];
                idx = i-k;
            }
            dp[i][1] = maxVal;
            
            memo[i-1][1] = idx; // 走到某點要構成最大值 的那個區間的頭?
        }

        maxVal = 0;
        for(int i = 2*k; i <= n-k; i++){
            if(maxVal < presum[i] - presum[i-k] + dp[i-k][1]){
                maxVal = presum[i] - presum[i-k] + dp[i-k][1];
                idx = i - k;
            }
            dp[i][2] = maxVal;
            
            memo[i-1][2] = idx;
        }

        // -1 x x x | x x x | x x x | x x x x x x x x x  k = 3
        maxVal = 0;
        for(int i = k*3; i <= n; i++){
            if(maxVal < presum[i] - presum[i-k] + dp[i-k][2]){
                maxVal = presum[i] - presum[i-k] + dp[i-k][2];
                idx = i - k;
            }
            dp[i][3] = maxVal;
            memo[i-1][3] = idx;
        }

        // now we know the start of third inteval is idx
        vector<int> res(3);
        int count = 2;
        
        while(count >= 0){
            res[count] = idx;
            count -= 1;
            if(idx-1 >= 0) idx = memo[idx-1][count+1];
        }

        return res;
    }
};

/*
dp[i][j] -> 走到 i 位置 時 已經選了0-2個 可以產生的最大sum 
n = 10^4 大概可以接受 nlgn 
*/
