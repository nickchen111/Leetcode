/*
2719. Count of Integers
*/

// 優化寫法 其實isLimit 為true時不會有重複運算的狀況 所以不用記憶化
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        int mn = num1.size();
        int mx = num2.size();
        auto check = [&](string& s) -> bool {
            int sum = 0;
            for(auto &ch : s) {
                sum += (ch-'0');
            }

            return (sum >= min_sum && sum <= max_sum);
        };
        // vector<vector<vector<LL>>> memo(mx, vector<vector<LL>>(max_sum+1, vector<LL>(2,-1)));
        vector<vector<LL>> memo(mx, vector<LL>(max_sum+1, -1));
        function<LL(string&,int,int,bool,bool)> f = [&](string&s, int i, int sum, bool isLimit, bool isNum) -> LL {
            if(sum > max_sum) return 0;
            if(i == s.size()) {
                return (isNum && sum >= min_sum);
            }
            LL res = 0;
            if(memo[i][sum] != -1 && !isLimit) return  memo[i][sum];
            if(!isNum) res = f(s, i+1, sum, false, false);
            int up = isLimit ? s[i]-'0' : 9;
            
            for(int j = 1 - (isNum); j <= up; j++) {
                res = (res + f(s, i+1, sum+j, isLimit && j == up, true)) % MOD;
            }
            
            return memo[i][sum] = res;
        };

        LL res = f(num2, 0, 0, true, false);
        memo.clear();
        memo.resize(mn, vector<LL>(max_sum+1, -1));
        // memo.resize(mx, vector<vector<LL>>(max_sum+1, vector<LL>(2,-1)));
        res = ((res - f(num1, 0, 0, true, false)) % MOD + MOD) % MOD;
    
        if(check(num1)) {
            res += 1;
            res %= MOD;
        }

        return res;

    }
};

// TC: O(9*n*22*2)  n 為最大值max_sum SC:O(2*25*n)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        int mn = num1.size();
        int mx = num2.size();
        auto check = [&](string& s) -> bool {
            int sum = 0;
            for(auto &ch : s) {
                sum += (ch-'0');
            }

            return (sum >= min_sum && sum <= max_sum);
        };
        vector<vector<vector<LL>>> memo(mx, vector<vector<LL>>(max_sum+1, vector<LL>(2,-1)));
        function<LL(string&,int,int,bool,bool)> f = [&](string&s, int i, int sum, bool isLimit, bool isNum) -> LL {
            if(sum > max_sum) return 0;
            if(i == s.size()) {
                return (isNum && sum >= min_sum);
            }
            LL res = 0;
            if(memo[i][sum][isLimit] != -1) return  memo[i][sum][isLimit];
            if(!isNum) res = f(s, i+1, sum, false, false);
            int up = isLimit ? s[i]-'0' : 9;
            
            for(int j = 1 - (isNum); j <= up; j++) {
                res = (res + f(s, i+1, sum+j, isLimit && j == up, true)) % MOD;
            }
            
            return memo[i][sum][isLimit] = res;
        };

        LL res = f(num2, 0, 0, true, false);
        memo.clear();
        memo.resize(mx, vector<vector<LL>>(max_sum+1, vector<LL>(2,-1)));
        res = ((res - f(num1, 0, 0, true, false)) % MOD + MOD) % MOD;
    
        if(check(num1)) {
            res += 1;
            res %= MOD;
        }

        return res;

    }
};
