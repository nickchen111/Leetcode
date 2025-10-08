// TC:O(logn) SC:O(logn)
class Solution {
    using ll = long long;
public:
    long long countNoZeroPairs(long long n) {
        /*
        數位DP 去計算有多少個符合條件的可能性
        細節上要思考這幾個參數 1. 走到哪個位數 從低位到高位 2. 右邊的數字是否有向我借位? 3. 是否後面會是前導0
        */
        string s = to_string(n);
        int m = s.size();
        vector memo(m, array<array<ll, 2>, 2>({{-1, -1}, {-1, -1}}));
        auto two_sum_ways = [&](int target) -> ll {
            return max(min(target - 1, 19 - target), 0);
        };
        auto dfs = [&] (this auto &&dfs, int i, bool borrowed, bool is_num) -> ll {
            if (i < 0) {
                return !borrowed;
            }

            ll& ans = memo[i][borrowed][is_num];
            if (ans != -1) return ans;
            ans = 0;

            // 考慮是否有借位?
            int d = s[i] - '0' - borrowed;
            // 考慮是否會是前導零 如果是該數字d不能是0 除非兩者都是前導零
            if (is_num) { // 兩個都不是0
                ans = dfs(i - 1, false, true) * two_sum_ways(d); // 不向高位借1
                ans += dfs(i - 1, true, true) * two_sum_ways(d + 10);
            }

            // 其中一個數字有前導零
            if (i < m - 1) {
                if (d) { // 目前目標要不為0才能繼續做下去
                    ans += dfs(i - 1, d < 0, false) * (is_num + 1); // 根據對稱性 is_num = true 要乘二
                }
                else if (i == 0) ans += 1;
            }

            return ans;
        };
        return dfs(m - 1, false, true);
    }
};
