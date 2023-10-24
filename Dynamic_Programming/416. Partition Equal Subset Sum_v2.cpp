/*
416. Partition Equal Subset Sum
*/

//用已知推估未知 TC:O(N*sum) SC:O(N*Sum)
class Solution {
    int dp[201][20005];
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(), 0);
        if(sum%2 != 0) return false;//奇數就絕對是無解
        dp[0][0] = true; //沒指定物品且不需任何sum的可能是有的
        int n = nums.size();
        nums.insert(nums.begin(), 0);

        for(int i = 1; i <=n; i++){
            for(int s = 0; s<=sum/2; s++){
                dp[i][s] = dp[i-1][s] || (s-nums[i]>=0 && dp[i-1][s-nums[i]]);//選or不選有一個是true即可
                //s-nums[i]是為了避免越界
            }
        }

        return dp[n][sum/2];

    }
};

//假設現在狀態為true 推估未來
class Solution {
    int dp[201][20005];
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(), 0);
        if(sum%2 != 0) return false;//奇數就絕對是無解
        dp[0][0] = true; //沒指定物品且不需任何sum的可能是有的
        int n = nums.size();
        nums.insert(nums.begin(), 0);

        for(int i = 0; i < n; i++){
            for(int s = 0; s<=sum/2; s++){
                if(dp[i][s]){
                    dp[i+1][s] = true;
                    dp[i+1][s+nums[i+1]] = true;
                }
            }
        }

        return dp[n][sum/2];

    }
};


/*
01背包問題
一個想法是
外層遍歷物品 內層遍歷sum的選項
dp[i] 如果前面可以找到dp[i-x] 為可以裝得下 那麼 dp[i]肯定可以符合
另一個想法是dp[i][s] 為在 i個物品內 能否加總出s的總和
from the first element i, if there is a way to pick some number whose sum equals to s 
選擇就會是加or 不加
兩種寫法
1. 用已知推估未來
dp[i-1][s] == true -> dp[i][s] == true 不選
dp[i-1][s-nums[i]] == true -> dp[i][s] == true 選
2.用未來推估未來
if(dp[i][s]成立) dp[i+1][s+nums[i+1]]也會成立 
                dp[i+1][s]也成立
此題也可以用DFS做 但會TLE
*/
