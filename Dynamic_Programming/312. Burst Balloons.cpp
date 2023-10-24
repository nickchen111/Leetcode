/*
312. Burst Balloons
*/

//區間型DP 主要是要想到用戳破最後一個氣球來定義DP
//TC:O(n^3) SC:O(n^2)
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        //區間型DP套路
        for(int len = 1; len<=n; len++){
            for(int i = 1; i+len-1<=n; i++){
                int j = i+len-1;
                for(int k = i; k<=j; k++)
                    dp[i][j] = max(dp[i][j],dp[i][k-1]+dp[k+1][j] + nums[k]*nums[i-1]*nums[j+1]);
            }
        }

        return dp[1][n];
    }
};

/*
dp[i][j] i > j的狀況
dp[i][j]定義為 maximum coins you can collect by bursting the balloons[i:j]
每次都去選一個當作最後戳破的氣球 如果是選第一次戳破的氣球會變得相當複雜
dp[i][j] = dp[i][k-1]+dp[k+1][j] + nums[k]*nums[i-1]*nums[j+1]
要考量邊界條件 
1.dp[i][j] i > j的狀況 設為0也就是那邊不會有值 在加法上沒問題
2.nums[i-1跟nums[j+1] 題目有說設為1 代表就算從頭or尾作為戳破的氣球 數值也不會乘上0而導致不列入計算

i x x x x x [k] x x x x j
*/
