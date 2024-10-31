/*
920. Number of Music Playlists
*/

// Math 容斥 + 全排列組合 + 除法同餘 + 乘法快速冪 TC:O(n*lg(goal-k)) SC:O(n)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int numMusicPlaylists(int n, int goal, int k) {
        function<LL(LL a, LL b)> quickMul = [&](LL a, LL b) -> LL {
            LL ans = 1;
            while(b) {
                if(b & 1) {
                    ans = (ans * a) % MOD;
                }
                a = (a*a) % MOD;
                b >>= 1;
            }

            return ans;
        };

        vector<LL> fac(n+1);
        vector<LL> inv(n+1);
        // 建造 階級的 fac 與逆元 
        auto build = [&](LL limit) {
            fac[1] = 1;
            for(int i = 2; i <= limit; i++) {
                fac[i] = ((LL) i * fac[i-1]) % MOD;
            }

            inv[limit] = quickMul(fac[limit], MOD-2);
            for(int i = limit - 1; i >= 0; i--) {
                inv[i] = ((LL) (i+1) * inv[i+1]) % MOD;
            }
        };
        build(n);
        LL res = 0;
        LL sign = 1;
        for(int i = 0; i <= n-k-1; i++, sign = (sign == 1 ? (MOD-1):1)) {
            LL cur = fac[n];
            cur = (cur * quickMul(n-k-i,goal-k)) % MOD;
            cur = (cur * inv[n-i-k]) % MOD;
            cur = (cur * inv[i]) % MOD;
            cur = (cur * sign) % MOD;
            res = (res + cur) % MOD;
        }

        return res;
    }
};

// DP TC:O(n*goal) SC:O(n*goal -> goal)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int numMusicPlaylists(int n, int goal, int k) {
        vector<vector<LL>> dp(goal+1, vector<LL>(n+1));
        dp[0][0] = 1;
        for(int i = 1; i <= goal; i++) {
            for(int j = 1; j <= n; j++) {
                dp[i][j] = (dp[i][j] + dp[i-1][j-1] * (n-j+1)) % MOD;
                dp[i][j] = (dp[i][j] + dp[i-1][j] * max(0, j-k)) % MOD;
            }
        }

        return dp[goal][n];
    }
};


/*
有規則的題目做久了就發現首先要去想沒有限制的狀況要怎麼求答案
1. 假設每首歌沒有限制一定要播放
2. 假設不限制k首歌的interval -> k^l 那現在把限制加回去
(1 2 3...k) k+1這裡之後可以放0 or 除了{2,3....k}以外的數字 = n - k個數字
(1 2 3 ... k k+1) 他可以是 pn取k -> n!/(n-k-1)!
所以就會是 n!/(n-k-1)! * (n-k)^(goal-k-1) = f(n, goal, k)
n!/(n-k-1)! * (n-k)^(goal-k-1) = n!/(n-k-1)! * (n-k)^(goal-k)/(n-k) = n!*((n-k)^(goal-k))/(n-k)!
n! -> factorial 去處理 
1/(n-k)! 逆元階級處理
n-k ^ 就是乘法快速冪 或者也可以預處理
再來就把限制加回來 限制每首歌都要放 那就會是
沒有限制狀況 - 沒1 - 沒2 - 沒3 - .... 一個限制的話就是 f(n-1,k,k) cn取1
+ 沒1與沒2 + .... 兩個就是 f(n-2,l,k) 個數就是cn取2
所以換成公式就會是 sum(  (-1)^i * Cn取i * f(n-i,l,k)   )
就會是 (-1)^i * (n!/(n-i)!*(i!)) * (n-i)!*((n-k-i)^(goal-k))/(n-k-i)!
變成 (-1)^i * (n! * (n-k-i)^(goal-k)) / (i! * (n-k-i)!)
但如果 n < k 就不用算惹 所以i會有限制上限
n-i > k -> i < n - k 也就是 i <= n - k - 1

DP :
dp[i][j] 用了j首歌都要選時 可以拼湊出長度為i 不能有間隔k以下重複選同首歌的方案數
dp[i][j] = dp[i-1][j-1]*(n-j+1) 不用之前選過的歌的話
dp[i][j] += dp[i-1][j]*max(0, j-k); 用之前選過的歌曲的話
*/
