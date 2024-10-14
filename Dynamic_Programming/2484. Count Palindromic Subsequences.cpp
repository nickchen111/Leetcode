/*
2484. Count Palindromic Subsequences
*/

// TC:O(100*n + 10*n) SC:O(100)
class Solution {
    const long MOD = 1e9 + 7;
public:
    int countPalindromes(string s) {
        int suf[10]{}, suf2[10][10]{}, pre[10]{}, pre2[10][10]{};
        for (int i = s.length() - 1; i >= 0; --i) {
            char d = s[i] - '0';
            for (int j = 0; j < 10; ++j)
                suf2[d][j] += suf[j];
            ++suf[d];
        }

        long ans = 0L;
        for (char d : s) {
            d -= '0';
            --suf[d];
            for (int j = 0; j < 10; ++j)
                suf2[d][j] -= suf[j]; // 撤销
            for (int j = 0; j < 10; ++j)
                for (int k = 0; k < 10; ++k)
                    ans += (long) pre2[j][k] * suf2[j][k]; // 枚举所有字符组合
            for (int j = 0; j < 10; ++j)
                pre2[d][j] += pre[j];
            ++pre[d];
        }
        return ans % MOD;
    }
};

// 次佳解 TC:O(100*n + n*(n+1)/2) SC:O(100*n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int countPalindromes(string s) {
        int n = s.size();
        vector<vector<LL>> suffix(n+1, vector<LL>(100));
        for(int i = n-1; i >= 0; i--){
            suffix[i] = suffix[i+1];
            LL num = (s[i]-'0');
            for(int j = i+1; j < n; j++){
                LL cur = num + (s[j]-'0')*10;
                suffix[i][cur] += 1;
            }
        }

        vector<LL> prefix(100); 
        LL res = 0;
        for(int i = 2; i < n-2; i++) {

            for(int j = 0; j < i-1; j++){
                LL num = (s[i-1]-'0') + (s[j]-'0')*10;
                prefix[num] += 1;
            }

            for(int j = 0; j < 100; j++) {
                res =  (res + (LL)prefix[j]*suffix[i+1][j]) % M;
            }
        }

        return res;

        
    }
};

/*
要如何判斷前後字段一樣
*/
