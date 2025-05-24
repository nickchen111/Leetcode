// TC:O(n * n * sqrt(U)) U 為數值大小 SC:O(m) m 為儲存的質數數量 不超過 n * n 個
class Solution {
    using ll = long long;
public:
    long long sumOfLargestPrimes(string s) {
        int n = s.size();
        set<ll> primes; 
        for (int i = 0; i < n; i++) {
            ll x = 0;
            for (int j = i; j < n; j++) {
                x = x * 10 + (s[j] - '0');
                if (x < 2) continue;
                if (x == 2) {
                    primes.insert(x);
                    continue;
                }
                if (x % 2 == 0) continue;
                bool flag = true;
                for (ll k = 3; k * k <= x; k += 2) {
                    if (x % k == 0) {
                        flag = false;
                        break;
                    }
                }
                if (flag) primes.insert(x);
            }
        }

        ll ans = 0;
        auto it = primes.rbegin();
        for (int cnt = 0; cnt < 3 && it != primes.rend(); ++cnt, ++it) {
            ans += *it;
        }

        return ans;
    }
};
