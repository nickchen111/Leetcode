// 遞歸 如果要寫成遞推可以用set才不會超時 TC:O((n+m)kt) SC:O(nkt) Bitset: TC:O(mkt/w) m 為 edges數量 SC:O(nkt/w)
// 似乎還可以用拓墣排序做
static const int MAXSTEP = 601;
class Solution {
public:
    int maxWeight(int n, vector<vector<int>>& edges, int k, int t) {
        // Bitset作法
        vector f(k + 1, vector<bitset<600>>(n));
        for (int i = 0; i < n; i++) {
            f[0][i].set(0);
        }
        for (int i = 0; i < k; i++) {
            for (auto& e : edges) {
                int x = e[0], y = e[1], wt = e[2];
                f[i + 1][y] |= f[i][x] << wt;
            }
        }

        int ans = -1;
        for (auto& bit : f[k]) {
            for (int s = t - 1; s >= 0; s--) {
                if (bit.test(s)) {
                    ans = max(ans, s);
                    break;
                }
            }
        }
        return ans;
        
        /*
        vector<vector<pair<int,int>>> next(n);
        for (auto &e : edges) {
            next[e[0]].emplace_back(e[1], e[2]);
        }
        
        vector<unordered_map<int, int>> memo(n * (k+1));
        
        auto dfs = [&](this auto&&dfs, int node, int cnt, int sum) -> int {
            if (sum >= t) return -1;
            if (cnt == k) return sum;
            int idx = node * (k+1) + cnt;
            
            // auto it = memo[idx].find(sum);
            if (memo[idx].find(sum) != memo[idx].end()) {
                return memo[idx][sum];
            }
        
            int ans = -1;
            for (auto [nxt, w] : next[node]) {
                ans = max(ans, dfs(nxt, cnt + 1, sum + w));
            }
            
            memo[idx][sum] = ans;
            return ans;
        };
        int answer = -1;
        for (int i = 0; i < n; i++) {
            answer = max(answer, dfs(i, 0, 0));
        }
        
        return answer;
        */
    }
};
