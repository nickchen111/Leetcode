/*
486. Predict the Winner
*/

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
