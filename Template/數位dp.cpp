/* v1模板
從i 開始填數字，i前面填的數字集合是mask，此時可以構造出的數目
isLimit 表示前面填的數字是否都是n對應位上的，如果為true,那麼當前位至多為int(s[i]),否則至多9
isNum 表示前面是否填了數字(是否跳過)，如果為true，當前位可以從0開始，如果false 那麼我們可以跳過，或者從1開始填數字
記得memo
*/
vector<vector<LL>> memo(mx, vector<LL>(max_sum+1, -1));
auto f = [&](auto &&f, int i, int mask, bool isLimit, bool isNum) -> int {
            if(i == n) return isNum; // 是否有構成一個數字而不是跳過
            int res = 0;
            if(memo[i][sum] != -1 && !isLimit && isNum) return  memo[i][sum];
            if(!isNum) res = f(f, i+1, mask, false, false);
            int up = isLimit ? s[i]-'0' : 9;
            
            for(int j = 1 - (isNum); j <= up; j++) {
                        if(((mask >> j) & 1) == 0) res += f(f, i+1, mask|(1<<j), isLimit & j == up, true);
            }
            
            if(!isLimit && isNum) memo[i][sum] = res;
            
            return res;
};

return f(f, 0,0, true, false); // 剛開始初始化為true，如果一開始是false那就代表後面怎麼填都可以

/*
當前最終版v2.1
*/

class Solution {
public:
    int beautifulNumbers(int l, int r) {
        string low = to_string(l), high = to_string(r);
        int n = high.size();
        int diff_lh = n - low.size(); // 这样写无需给 low 补前导零，也无需 is_num 参数
        unordered_map<long long, int> memo;

        auto dfs = [&](this auto&& dfs, int i, int m, int s, bool limit_low, bool limit_high) -> int {
            if (i == n) {
                return s && m % s == 0;
            }
            long long mask = (long long) m << 32 | i << 16 | s; // 三个 int 压缩成一个 long long
            if (!limit_low && !limit_high && memo.contains(mask)) {
                return memo[mask];
            }

            int lo = limit_low && i >= diff_lh ? low[i - diff_lh] - '0' : 0;
            int hi = limit_high ? high[i] - '0' : 9;

            int res = 0;
            int d = lo;
            if (limit_low && i < diff_lh) { // 這裡判斷說是否是limit_low有的話代表貼著但他不可能有東西所以其實是!isNum
                res = dfs(i + 1, 1, 0, true, false); // 什么也不填
                d = 1; // 下面循环从 1 开始 後面才會開始有值
            }
            for (; d <= hi; d++) {
                res += dfs(i + 1, m * d, s + d, limit_low && d == lo, limit_high && d == hi);
            }

            if (!limit_low && !limit_high) {
                memo[mask] = res;
            }
            return res;
        };

        return dfs(0, 1, 0, true, true);
    }
};
