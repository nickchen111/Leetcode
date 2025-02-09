// TC:O(n * D^2) D = 數字範圍 SC:O(D^2) -> O(D)
class Solution {
    using LL = long long;
public:
    long long countSubstrings(string s) {
        int n = s.size();
        LL ans = 0;
        for(int i = 1; i <= 9; i++) {
            vector<int> cnt(i);
            // cnt[0] = 1;
            for(int j = 0; j < n; j++) {
                vector<int> tmp(i);
                for(int k = 0; k < i; k++) {
                    if(cnt[k])
                        tmp[(k * 10 + s[j] - '0') % i] += cnt[k];
                }
                tmp[(s[j] - '0') % i] += 1;
                if(s[j] - '0' == i) ans += tmp[0];
                cnt = tmp;
            }
        }
        return ans;
        /*
        dp 角度切入寫法 
        vector dp(10, vector<int>(9));
        for(int i = 0; i < n; i++) {
            // 枚舉當下要更新的模數
            for(int j = 1; j <= 9; j++) {
                vector<int> tmp(9);
                tmp[(s[i] - '0') % j] = 1;
                for(int k = 0; k < j; k++) {
                    tmp[(k * 10 + s[i] - '0') % j] += dp[j][k];
                }
                dp[j] = tmp;
            }
            ans += dp[s[i] - '0'][0];
        }
        
        return ans;
        */
    }
};
