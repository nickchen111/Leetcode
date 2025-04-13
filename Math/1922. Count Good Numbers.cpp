// TC:O(lgn) SC:O(lgn)
class Solution {
    using ll = long long;
    ll MOD = 1e9 + 7;
public:
    int countGoodNumbers(long long n) {
        auto quickMul = [&](ll a, ll b) -> ll {
            ll ans = 1;
            while (b) {
                if (b & 1) {
                    ans = (ans * a) % MOD;
                }
                b >>= 1;
                a = (a * a) % MOD;
            }
            return ans;
        };
        /*
        問說長度為n的數字有哪些符合 偶數位為偶數，奇數位為prime(2,3,5,7) 四種
        那就是數學了 嘗試第一位可以填 5 *  
        */
        return quickMul(5, (n + 1) / 2) * quickMul(4, n / 2) % MOD;
    }
};
