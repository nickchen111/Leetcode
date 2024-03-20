/*
3077. Maximum Strength of K Disjoint Subarrays
*/

// TC:O(n*k) SC:O(n*k*2)
class Solution {
    using LL = long long;
public:
    long long maximumStrength(vector<int>& nums, int k) {
        int n = nums.size();
        nums.insert(nums.begin(),-1);
        vector<vector<vector<LL>>> dp(n+1, vector<vector<LL>>(k+1, vector<LL>(2,LLONG_MIN/2)));
        for(int i = 0; i <= n; i++){
            dp[i][0][0] = 0;
            //dp[i][0][1] = 0;
        }

        dp[1][0][0] = 0;

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= k; j++){
                if(j % 2 == 0){
                    // do not pick
                    dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1]);
                    dp[i][j][1] = max(dp[i-1][j-1][0], dp[i-1][j-1][1]) - (LL)nums[i]*(k+1-j);
                    dp[i][j][1] = max(dp[i][j][1], dp[i-1][j][1] - (LL)nums[i]*(k+1-j));
                }
                else {
                    dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1]);
                    dp[i][j][1] = max(dp[i-1][j-1][0], dp[i-1][j-1][1]) + (LL)nums[i]*(k+1-j);
                    dp[i][j][1] = max(dp[i][j][1], dp[i-1][j][1] + (LL)nums[i]*(k+1-j));
                }
            }
        }


        return max(dp[n][k][0], dp[n][k][1]);
    }
};

/*
(-1)i+1 * sum[i] * (x - i + 1) 越前面數字可以被乘的越大
只要是選取的第奇數個subarray就會是正數 所以他的sum最好也是正數 i從1開始算
必須選k個
the selected subarrays don't need to cover the entire array.
這題題意不清楚 其實只能按照順序的取 那就可以看得出來是區間型的dp
dp[i][j] : the max strength by finding the first j subarrays from nums[1:i]
-> sum[1]*k - sum[2]*(k-1) + sum[3]*(k-2)-...

x x x x x x x i
兩種情況
1. do not pick nums[i] : dp[i][j] = dp[i-1][j];
suppose k% 2 == 0
2. do pick nums[i] : dp[i][j] = dp[i-1][j-1] - nums[i]*(k+1-j); 自成一國
                     dp[i][j] = dp[i-1][j] - nums[i]*(k+1-j);  這裡是想要跟前面的合併但會發現我們的定義沒有說 前面i-1個肯定會用
多＋一個維度
dp[i][j][0] : the max strength by finding the first j subarrays from nums[1:i] and nums[i] is not part of sum[j]
dp[i][j][1] : the max strength by finding the first j subarrays from nums[1:i]and nums[i] is part of sum[j]
*/
