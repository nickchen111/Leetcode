/*
2827. Number of Beautiful Integers in the Range
*/

// TC:O(m^2 * k * 10) m 為字串長度，k為餘數範圍 SC:O(m^2 * k )
class Solution {
public:
    int numberOfBeautifulIntegers(int low, int high, int k) {
        auto countBeautiful = [&](int n) {
            string s = to_string(n);
            int m = s.size();
            vector<vector<vector<int>>> memo(m, vector<vector<int>>(2 * m + 1, vector<int>(k, -1)));
            
            function<int(int, int, int, bool, bool)> dfs = [&](int i, int count, int mod, bool isLimit, bool isNum) -> int {
                if (i == m) {
                    return isNum && count == 0 && mod == 0;
                }
                if (!isLimit && isNum && memo[i][count + m][mod] != -1) {
                    return memo[i][count + m][mod];
                }

                int res = 0;
                if (!isNum) {
                    res += dfs(i + 1, count, mod, false, false);
                }

                int up = isLimit ? s[i] - '0' : 9;
                for (int j = isNum ? 0 : 1; j <= up; ++j) {
                    int newCount = count + (j % 2 == 1 ? 1 : -1);
                    int newMod = (mod * 10 + j) % k;
                    res += dfs(i + 1, newCount, newMod, isLimit && j == up, true);
                }

                if (!isLimit && isNum) {
                    memo[i][count + m][mod] = res;
                }
                return res;
            };

            return dfs(0, 0, 0, true, false);
        };

        return countBeautiful(high) - countBeautiful(low - 1);
    }
};


/*
odd == even number #
數字要被k整除
1000000000 -> 10位數 所以奇數偶數會是 10*10 但也可以直接轉成20 10代表balance
再來處理low ~ high 那就是 process(high) - process(low)
5 % 4 = 1
50 % 4 = 2
500 % 4 = 0
*/
