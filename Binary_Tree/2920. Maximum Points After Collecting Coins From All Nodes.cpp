/*
2920. Maximum Points After Collecting Coins From All Nodes
*/

// 1205
class Solution {
public:
    int maximumPoints(vector<vector<int>>& edges, vector<int>& coins, int k) {
        int n = coins.size();
        vector<vector<int>> next(n);
        for(auto &e : edges) {
            next[e[0]].push_back(e[1]);
            next[e[1]].push_back(e[0]);
        }
        auto Reduced = [&](int num, int time) -> int {
            if(time >= 14) return 0;
            while(time--) {
                num /= 2;
            }
            return num;
        };
        vector<vector<int>> memo(n, vector<int>(15,-1));
        auto dfs = [&](auto && dfs, int cur, int prev, int time) -> int {
            if(time >= 14) time = 14;
            if(memo[cur][time] != -1) return memo[cur][time];
            int mustdo = Reduced(coins[cur], time);
            int cand1 = mustdo - k;
            int cand2 = mustdo/2;
            for(auto &nxt : next[cur]) {
                if(nxt != prev) {
                    cand1 += dfs(dfs, nxt, cur, time);
                    cand2 += dfs(dfs, nxt, cur, time + 1);
                }
            }

            return memo[cur][time] = max(cand2,cand1);
        };
        return dfs(dfs, 0, -1, 0);
    }
};

/*
堅持用n/2 去得分 那後面的就也都要/2
會除很多次 10^4 大概是14次最多
*/

// TC:O(15*n) SC:O(15*n)
class Solution {
    vector<int> next[100005];
    int memo[100005][14]; // 2^13 = 8192 
public:
    int maximumPoints(vector<vector<int>>& edges, vector<int>& coins, int k) {
        for(auto edge : edges){
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }
        for(int i = 0; i < coins.size(); i++){
            for(int j = 0; j < 14; j++){
                memo[i][j] = INT_MIN;
            }
        }

        return DFS(-1,0,0,coins,k);
    }

    int DFS(int parent, int times, int cur, vector<int>& coins, int k){

        // case1 - k
        if(times >= 14) times = 13;
        if(memo[cur][times] != INT_MIN) return memo[cur][times];
        int sum1 = Reduced(coins[cur],times) - k;
        // case2 x /= 2;
        int sum2 = Reduced(coins[cur],times)/2;
        for(auto child : next[cur]){
            if(child == parent) continue;
            sum1 += DFS(cur, times, child, coins, k);
            sum2 += DFS(cur, times+1, child, coins, k);
        }

        memo[cur][times] = max(sum1, sum2);

        return max(sum1, sum2);
    }
    int Reduced(int x, int times){
        for(int i = 0; i < times; i++){
            x = x / 2;
        }
        return x;
    }
};

/*
收集樹上硬幣parent收集完之前child不能被取 
每次取硬幣可以有兩種選擇 1. 當下硬幣-k 2. 當下硬幣/2 加入 但之後的子樹上的硬幣也都要除二

*/
