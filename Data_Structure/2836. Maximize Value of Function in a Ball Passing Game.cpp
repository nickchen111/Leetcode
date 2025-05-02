// TC:O(n * lgk) SC:O(n * lgk)
class Solution {
    using ll = long long;
public:
    long long getMaxFunctionValue(vector<int>& receiver, long long k) {
        /*
        一個玩家拋球給其他玩家傳遞k次 需要知道可以傳遞給哪些玩家，並且需要求出在走k步內的狀況下
        來說，哪個玩家開始傳遞會得到最大的玩家編號累加和
        那就是st表 兩個 1. 某玩家傳遞k步可以走到哪 2. 某玩家走K步的最大和
        1. receiver 需要創建鄰接表
        2. 使用鄰接表跑DFS求出每個玩家走k能到哪
        */
        int n = receiver.size();
        ll sz = bit_width((unsigned long long)k); // sz = 64 - __builtin_clzll(k); // 最大跳躍層數
        vector<vector<ll>> stjump(n, vector<ll>(sz + 1, -1));
        vector<vector<ll>> stsum(n, vector<ll>(sz + 1));
        auto build = [&]() -> void { // 現在在哪個index 
            for (int i = 0; i < n; i++) {
                stjump[i][0] = receiver[i];
                stsum[i][0] = receiver[i]; // 走一步可以有的sum
            }
            for(int j = 1; j <= sz; j++) {
                for (int i = 0; i < n; i++) {
                    stjump[i][j] = stjump[stjump[i][j - 1]][j - 1];
                    stsum[i][j] = stsum[i][j - 1] + stsum[stjump[i][j - 1]][j - 1];
                }
            }
        };
        build();
        ll ans = 0;
        // 預處理k有哪些步要跳
        vector<int> steps;
        for (int j = 0; j <= sz; j++) {
            if ((k >> j) & 1) { // 取出會跳的步數
                steps.emplace_back(j);
            }
        }
        for (int i = 0; i < n; i++) {
            ll sum = i;
            int cur = i;
            for (int j = 0; j < steps.size(); j++) {
                sum += stsum[cur][steps[j]];
                cur = stjump[cur][steps[j]];
            }
            ans = max(ans, sum);
        }
        return ans;
    }
};
