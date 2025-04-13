// python 的進制太狗了 故此加上C++版本
class Solution {
    using ll = long long;
    ll MOD = 1e9 + 7;
    string trans(string& s, int b) {
        for (char& c : s) {
            c -= '0';
        }
        string digits;
        while (!s.empty()) {
            string nxt_s; // s / b 的结果
            int rem = 0; // s % b 的结果
            for (char c : s) {
                rem = rem * 10 + c;
                int q = rem / b; // 商
                if (q || !nxt_s.empty()) {
                    nxt_s.push_back(q);
                }
                rem = rem % b;
            }
            digits.push_back(rem);
            s = move(nxt_s);
        }
        ranges::reverse(digits);
        return digits;
    }
    int check(const string &s) {
        int m = s.size();
        for (int i = 0; i < m - 1; i++) {
            if (s[i] > s[i + 1])
                return 0;
        }
        return 1;
    }
public:
    int countNumbers(string l, string r, int b) {
        string l_b = trans(l, b);
        string r_b = trans(r, b);
        auto countNumber = [&](string &s) -> ll {
            int n = s.size();
            vector memo(n, vector<vector<vector<ll>>>(2, vector<vector<ll>>(2, vector<ll>(10, -1))));
            auto dfs = [&](auto &&dfs, int i, bool is_num, bool is_limit, int prev) -> ll {
                if (i == n) return is_num ? 1 : 0;
                ll &res = memo[i][is_num][is_limit][prev];
                if (res != -1) return res;
                res = 0;
                if (!is_num) {
                    res = (res + dfs(dfs, i + 1, 0, 0, prev)) % MOD;
                }
                int up = is_limit ? (s[i]) : (b - 1);
                for (int digit = is_num ? prev : 1; digit <= up; digit++) {
                    res = (res + dfs(dfs, i + 1, 1, is_limit && (digit == up) ? 1 : 0, digit)) % MOD;
                }
                return res;
            };
            return dfs(dfs, 0, false, true, 0) % MOD;
        };
        return (countNumber(r_b) - countNumber(l_b) + check(l_b) + MOD) % MOD;
    }
};
