/*
2140. Solving Questions With Brainpower
*/

// TC:O(n) SC:O(n) RollingMax 正著寫
class Solution {
    using LL = long long;
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<LL> dp_take(n,0);
        vector<LL> dp_notake(n,0);
        LL res = 0;
        dp_take[0] = questions[0][0];
        vector<pair<int,int>> endTimes;
        for(int i = 0; i < questions.size(); i++){
            endTimes.push_back({questions[i][1]+i, i});
        }
        sort(endTimes.begin(), endTimes.end());
        
        for(int i = 0; i < n; i++){
            dp_take[i] = questions[i][0];
        }
        LL rollMax = 0;
        int p = 0;
        for(int i = 1; i < n; i++){
           while(p < n && endTimes[p].first < i){
               rollMax = max(rollMax, dp_take[endTimes[p].second]);
               p++;
           } 
           dp_take[i] = rollMax + questions[i][0];
           dp_notake[i] = max(dp_take[i-1], dp_notake[i-1]);
        }

        res = max(dp_notake[n-1], dp_take[n-1]);

        return res;
    }
};

//逆著寫  TC:O(n) SC:O(n) 
class Solution {
    using LL = long long;
public:
    long long mostPoints(vector<vector<int>>& questions) {
        int n = questions.size();
        vector<LL> dp(n+1);
        for(int i = n-1; i >= 0; i--){
            int j = i + questions[i][1] + 1;
            dp[i] = max(dp[i+1], (j < n ? dp[j]: 0) + questions[i][0]);
        }

        return dp[0];
    }
};

/*
總覺得此題跟2944有點像 這題是要求最大可以收集到的分數 並且如果取了後面被限制的肯定不能取
選了現在這個問題 之後幾個問題就不能作答 1~10^5
dp[i] 到i為止能獲得的最大分數

填表法：現在的分數取決於過去已知
not pick dp[i] =  dp[i-1]
pick dp[i] = dp[j] + val[i] where j + skip[j] < i 
他也是要考慮到
dp[j-1]  dp[j] -> dp[i]
  take   notake         take
無從保證dp[j-1] 沒有cover到dp[i]

刷表法： 現在分數已知 來推論未來分數
dp[i+1] = max(dp[i+1], dp[i]) do not pick i+1 item
dp[j] = max(dp[j], dp[i] + val[j]) where j = i + skip[i] + 1 pick j th item
會遇到一樣問題
dp[i-1]  dp[i] -> dp[j]
  take   notake         take
dp[i-1]那項冷凍期特別長 又限制了你刷新dp[j]的資格

雙狀態 TO DO OR NOT TO DO
dp[i]_take dp[i]_notake
the maximum gain after addressing problem [0:i] we do or do not pick ith item
現在的take就沒有單調性 就沒辦法 找最近的當作答案 所以需要 找對於目前的i合法的範圍來更新
會變成n^2, 想到的解法是先將每個點能涵蓋到範圍取出來並且排序 一個rollmax去不斷紀錄可走到當前點的最大值
如果用刷表法寫的話等於要更新一個動態更新的diff數組 
最主流寫法：從後往前看！
dp[i] : the maximum gain after addressing problem [i:n-1]
do not pick : dp[i] = dp[i+1]
do pick : dp[i] = dp[i+skip[i] + 1] + val[i]
*/
