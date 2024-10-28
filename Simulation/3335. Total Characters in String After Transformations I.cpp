/*
3335. Total Characters in String After Transformations I
*/

// 矩陣快速冪 TC:O(m*m + m^3 * lgt) t = 最多10^9次數, m 為字母數量26 SC:O(26^2)
class Solution {
    using LL = long long;
    LL MOD = 1e9+7;
public:
    int lengthAfterTransformations(string s, int t) {
        vector<vector<LL>> start(1, vector<LL>(26));
        for(auto &ch : s) {
            start[0][ch-'a'] += 1;
        }
        vector<vector<LL>> base(26, vector<LL>(26));
        for(int i = 0; i < 26; i++) {
            if(i == 25){
                base[i][(i+1)%26] = 1;
                base[i][(i+2)%26] = 1;
            }
            else base[i][(i+1)%26] = 1;
        }

        vector<vector<LL>> a = multiply(start, pow(base, t));
        LL res = 0;
        for(LL &x : a[0]) {
            res = (res + x) % MOD;
        }

        return res;
    }
    vector<vector<LL>> multiply(const vector<vector<LL>>& a, const vector<vector<LL>>& b) {
        int n = a.size();
        int m = b[0].size();
        int k = a[0].size();
        vector<vector<LL>> res(n, vector<LL>(m));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int c = 0; c < k; c++) { 
                    res[i][j] = (res[i][j] + (LL)a[i][c] * b[c][j]) % MOD;
                }
            }
        }
        return res;
    }

    vector<vector<LL>> pow(vector<vector<LL>>& m, int p) {
        int n = m.size();
        vector<vector<LL>> res(n, vector<LL>(n));
        for (int i = 0; i < n; i++) {
            res[i][i] = 1; // 單位矩陣
        }

        for(; p != 0; p >>= 1) {
            if(p & 1) {
                res = multiply(res, m);
            }
            m = multiply(m, m);
        }
        return res;
    }
};

// 更好的解法是DP 此題數據規模可以用模擬 TC:O(26*t + n + 26) SC:O(26)
class Solution {
    using LL = long long;
public:
    int lengthAfterTransformations(string s, int t) {
        const int MOD = 1e9 + 7;
        vector<int> count(26, 0);
        
        
        for (char c : s) {
            count[c - 'a']++;
        }
        
        for (int i = 0; i < t; i++) {
            vector<int> next(26, 0);
            LL ab_count = count[25];
            count[25] = 0;
            
            for (int j = 0; j < 25; j++) {
                next[j + 1] += count[j];
            }
            
            next[0] += ab_count; 
            next[1] += ab_count; 
            
            for (int j = 0; j < 26; j++) {
                count[j] = next[j] % MOD;
            }
        }
        
        LL total = 0;
        for (int cnt : count) {
            total = (total + cnt) % MOD;
        }
        
        return total;
    }
};

/*
a 要轉25次變成z 
26變 ab 看他可以轉幾次26次 就會生成多少長度
ex : 3次, 1 : ab -> b轉到25變ab
25變 zab
26變 abbc
...

z -> ab
ab -> bc
bc ->de
de -> ef ...
*/
