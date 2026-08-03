class Solution {
    int n;
    vector<int> memo;
 public:
    string stoneGameIII(vector<int>& stoneValue) {
        n = stoneValue.size();
        memo = vector<int>(n+1,INT_MIN);
        vector<int> presum(n+1);
        for(int i = 1; i <= n; i++){
            presum[i] = presum[i-1] + stoneValue[i-1];
        }

        int sum1 = solve(0,stoneValue, presum);
        if(sum1 > presum[n] - sum1) return "Alice";
        else if(sum1 == presum[n] - sum1) return "Tie";
        else return "Bob";
    }

    int solve(int cur, vector<int>& stoneValue,  vector<int>& presum){
        int res = INT_MIN;
        if(memo[cur] != INT_MIN) return memo[cur];
        if(cur == n) return 0;
        if(cur == n-1) return stoneValue[cur];

        if(cur < n) res = max(res, stoneValue[cur] +  (presum[n] - presum[cur+1]) - solve(cur+1, stoneValue, presum));
        if(cur + 1 < n) res = max(res, stoneValue[cur+1] + stoneValue[cur] +  (presum[n] - presum[cur+2]) - solve(cur+2, stoneValue, presum));
        if(cur + 2 < n) res = max(res, stoneValue[cur+1] + stoneValue[cur] + stoneValue[cur+2] +  (presum[n] - presum[cur+3]) - solve(cur+3, stoneValue, presum));

        memo[cur] = res;
        
        return res;
    }
};

/*
Alice 獲得的分數會是 solve(i)拿了i個 i = 1~3 + sum[i+1 : n] - solve(i+1)
solve(0, stoneValue, presum)
res = value[cur] + (presum[n] - presum[cur+1]) - solve(cur+1,..);
res = value[cur] + value[cur+1] + (presum[n] - presum[cur+2]) - solve(cur+2,..);
res = value[cur] + value[cur+1] + value[cur+2] + (presum[n] - presum[cur+3]) - solve(cur+3,..);
取最大
*/ 