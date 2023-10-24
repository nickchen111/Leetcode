/*
1406. Stone Game III
*/

//recursion+memo TC:O(n) SC:O(n) 配合suf
class Solution {
    vector<int> memo;
    int suf[50001];
public:
    string stoneGameIII(vector<int>& stoneValue) {
        //recursion+memo

        int n = stoneValue.size();
        memo = vector<int>(n+1, INT_MIN);
        suf[n] = 0;
        for(int i = n-1; i>=0; i--){
            suf[i] = suf[i+1] + stoneValue[i];
        }
        int gain = dp(0, stoneValue);
        
        if(gain > suf[0]-gain) return "Alice";
        else if(gain < suf[0]-gain) return "Bob";
        else return "Tie";
    }

    int dp(int i, vector<int>& stoneValue){
        int n = stoneValue.size();
        if(i >= n) return 0;
        if(i == n-1) return stoneValue[n-1];
        if(memo[i] != INT_MIN) return memo[i];

        int sum = 0;
        for(int x = 1; x<=3; x++){
            if(i+x-1 >= n) break;
            sum +=stoneValue[i+x-1];
            memo[i] = max(memo[i], sum+suf[i+x]-dp(i+x,stoneValue));
        }

        return memo[i];
    }
};

//iterative TC:O(n) SC:O(n) 配合presum
class Solution {
    
public:
    string stoneGameIII(vector<int>& stoneValue) {
        //itertive

        int n = stoneValue.size();
        vector<int> dp(n+1, INT_MIN);

        vector<int> presum(n+1);
        presum[0] = 0;
        for(int i = 1; i<=n; i++){
            presum[i] = presum[i-1]+stoneValue[i-1];
        }
        dp[n] = 0;
        for(int i = n-1; i >= 0; i--){
            int sum = 0;
            for(int x = 1; x<=3; x++){
                if(i+x-1 >= n) break;//index
                sum +=stoneValue[i+x-1];//index
                dp[i] = max(dp[i], sum+presum[n]-presum[i+x]-dp[i+x]);
            }
        }
        if(dp[0] > presum[n]-dp[0]) return "Alice";
        else if(dp[0] < presum[n] - dp[0]) return "Bob";
        else return "Tie";
    }
};


/*
此題改變規則說每次都可以取前三個石頭 問說是誰贏了就return 誰 or 平手
dp[i] 代表說 從index i開始取石頭 取了0~3個 = x 哪個取法最後的數值比較大
sum += stoneValue[i+x-1];
dp[i] = max(dp[i], sum + suf[i+x]-dp(i+x));
*/
