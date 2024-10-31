/*
486. Predict the Winner
*/

// 遞歸 + 遞推 TC:O(n^2) SC:O(n^2)
class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();

        // vector<vector<int>> memo(n, vector<int>(n));
        // function<int(int l, int r)> dfs = [&](int l, int r) -> int{
        //     if(l == r) return nums[l];
        //     if(l > r) return 0;
        //     if(memo[l][r]) return memo[l][r];
        //     int res = 0;
        //     res = max(res, nums[l] + min(dfs(l+2,r), dfs(l+1,r-1)));
        //     res = max(res, nums[r] + min(dfs(l,r-2), dfs(l+1,r-1)));

        //     return memo[l][r] = res;
        // };

        // int first = dfs(0,n-1);

        // return first >= reduce(nums.begin(), nums.end(), 0) - first;
        vector<vector<int>> dp(n, vector<int>(n));
        for(int i = 0; i < n; i++) {
            dp[i][i] = nums[i];
            if(i + 1 < n) dp[i][i+1] = max(nums[i], nums[i+1]);
        }

        for(int i = n-3; i >= 0; i--) {
            for(int j = i + 2; j < n; j++) {
                dp[i][j] = max(nums[i] + min(dp[i+2][j], dp[i+1][j-1]), nums[j] + min(dp[i][j-2], dp[i+1][j-1]));
            }
        }

        return dp[0][n-1] >= reduce(nums.begin(), nums.end(), 0) - dp[0][n-1];
    }
};


// old
class Solution {
    int memo[21][21];
    int presum[21];
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        //dp定義為在這段區間內你能拿到的最大分數
        //懶得寫iterative 寫recursion +memo
        presum[0] = 0;
        for(int i=1; i<=n; i++){
            presum[i] = presum[i-1]+ nums[i-1];
        }

        int player1 = dp(0,n-1,nums); 
        
        return player1 >= presum[n] - player1; 
    }
    int dp(int i, int j, vector<int>& nums){
        if(i == j) return memo[i][j] = nums[i];

        if(memo[i][j] != 0) return memo[i][j];

        return memo[i][j] = max(presum[j+1]-presum[i] - dp(i+1,j,nums), presum[j+1]-presum[i] - dp(i,j-1,nums));
    }
};

//跟stone game一樣套路題
