// TC:O(DnlogU + UlogU) SC:O(Dn + U)
const int MX = 70001;
vector<int> divisors[MX];

int init = [] {
    for (int i = 1; i < MX; i++) {
        for (int j = i; j < MX; j += i) {
            divisors[j].emplace_back(i);
        }
    }
    return 0;
}();


class Solution {
    using ll = long long;
    ll MOD = 1e9 + 7;
public:
    int totalBeauty(vector<int>& nums) {
        /*
        倍數容斥 可以去求出每個數字有多少個子序列數量GCD是他
        */
        int mx = *max_element(nums.begin(), nums.end());

        vector<ll> tree(mx + 1);
        vector<int> time(mx + 1);
        int now = 0;
        auto update = [&](int i, ll val) -> void {
            while (i < tree.size()) {
                if (time[i] < now) {
                    time[i] = now;
                    tree[i] = 0;
                }
                tree[i] = (tree[i] + val) % MOD;
                i += i & -i;
            }
        };
        auto pre = [&] (int i) -> ll {
            ll ans = 0;
            while (i > 0) {
                if (time[i] == now) ans = (ans + tree[i]) % MOD;
                i &= i - 1; // i -= i & -i;
            }
            return ans;
        };

        vector<vector<int>> groups(mx + 1);
        for (auto &x : nums) {
            for (auto &y : divisors[x]) {
                groups[y].emplace_back(x);
            }
        }

        auto count_increasing_subsequence = [&](vector<int>& group) {
            now += 1;
            ll res = 0;
            for (auto &g : group) {
                ll cnt = (pre(g - 1) + 1) % MOD;
                update(g, cnt);
                res = (res + cnt) % MOD;
            }
            return res;
        };
        ll ans = 0;
        vector<ll> f(mx + 1);
        for (int i = mx; i > 0; i--) {
            f[i] = count_increasing_subsequence(groups[i]);
            for (int j = i * 2; j <= mx; j+= i) {
                f[i] = (f[i] - f[j] + MOD) % MOD;
            }
            ans = (ans + f[i] * (ll) i) % MOD;
        }

        return ans;
    }
};
