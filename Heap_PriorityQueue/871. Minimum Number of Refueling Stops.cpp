// 貪心 + 二分 TC:O(nlgn) SC:O(n)
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        // dp 作法 是定義成每到一個加油站 加了 i 次油可以走到得最遠距離
        int n = stations.size();
        vector<long> dp(n + 1, -1);
        dp[0] = startFuel;
        for(int i = 0; i < n; i++) {
            for(int j = i; j >= 0; j--) {
                if(dp[j] >= stations[i][0])
                    dp[j+1] = max(dp[j+1], dp[j] + stations[i][1]);
            }
        }
        for (int i = 0; i <= n; i++) {
            if (dp[i] >= target) {
                return i;
            }
        }
        return -1;
    }
};

// DP TC:O(n^2) SC:O(n)
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int pos = startFuel;
        if(pos >= target) return 0;
        int curFuel = 0;
        priority_queue<int, vector<int>, less<>> pq;
        int i = 0;
        int cnt = 0;
        while(pos < target) {
            // 流程 1. 看目前有哪些可以選去走路 所以先把可以選的加入
            while(i < stations.size() && stations[i][0] <= pos) {
                pq.push(stations[i][1]);
                i += 1;
            }
            if(!pq.empty()) {
                pos += pq.top();
                pq.pop();
                cnt += 1;
            }
            else return -1;
        }
        return cnt;
    }
};
