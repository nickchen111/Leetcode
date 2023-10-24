/*
2560. House Robber IV
*/


//二分搜索＋dp TC:O(lgN+n) SC: O(n)
class Solution {
    int dp[100001][2];
public:
    int minCapability(vector<int>& nums, int k) {
        int n = nums.size();

        int left = 0, right = INT_MAX/2;
        while(left < right){
            int mid = left + (right-left)/2;

            if(atLeastK(mid, nums, k)) right = mid;
            else left = mid+1;
        }

        return left;
    }

    bool atLeastK(int cap, vector<int>& nums, int k){
        int n = nums.size();
        dp[0][0] = 0;
        if(nums[0] <= cap) dp[0][1] = 1;
        else dp[0][1] = INT_MIN/2;

        for(int i = 1; i<n; i++){
            if(nums[i] > cap){
                dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
                dp[i][1] = INT_MIN/2;
            }
            else{
                dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
                dp[i][1] = dp[i-1][0] +1;
            }
        }

        return max(dp[n-1][0],dp[n-1][1]) >= k;

    }
};

//優化： TC:O(lgN+n) SC: O(1)
class Solution {
public:
    int minCapability(vector<int>& nums, int k) {
        int n = nums.size();

        int left = 0, right = INT_MAX/2;
        while(left < right){
            int mid = left + (right-left)/2;

            if(atLeastK(mid, nums, k)) right = mid;
            else left = mid+1;
        }

        return left;
    }

    bool atLeastK(int cap, vector<int>& nums, int k){
        int n = nums.size();
        int norob = 0;
        int rob;
        if(nums[0] <= cap) rob = 1;
        else rob = INT_MIN/2;

        for(int i = 1; i<n; i++){
            int rob_tmp = rob, norob_tmp = norob;
            if(nums[i] > cap){
                norob = max(rob_tmp, norob_tmp);
                rob = INT_MIN/2;
            }
            else{
                norob = max(rob_tmp, norob_tmp);
                rob = norob_tmp +1;
            }
        }

        return max(rob,norob) >= k;

    }
};


/*
此題想用最少的capacity(在每個家的時候可以偷的最大價值上限)  去得到最少偷到k個家的成就
capacity的推論: 用二分搜索 
cap : how many houses we can rob
判斷是否可以偷到k個家: 用dp
dp[i][0~1]偷到第i個家時 在當前的capacity下最多可以偷到幾個家
dp[i][0]: how many houses we can rob if we do not rob i-th house
dp[i][1]: how many houses we can rob if we rob i-th house
0代表不偷 1代表偷
*/
