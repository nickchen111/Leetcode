/*
902. Numbers At Most N Given Digit Set
*/

// TC:O(9*n) SC:O(n)
class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        int k = digits.size();
        string s = to_string(n);
        int m = s.size();
        vector<int> memo(m, -1);
        function<int(int i, bool isLimit, bool isNum)> dfs = [&](int i, bool isLimit, bool isNum) -> int {
            if(i == m) {
                return isNum;
            }

            if(!isLimit && isNum && memo[i] != -1) return memo[i];
            int res = 0;
            if(!isNum) res = dfs(i+1, false, false);
            int up = isLimit ? s[i]-'0' : stoi(digits.back());

            for(int j = 0; j < k; j++) {
                if(stoi(digits[j]) > up) break;
                res = res + dfs(i+1, isLimit && up == stoi(digits[j]), true);
            }

            if(!isLimit && isNum) memo[i] = res;
            return res;
        };
        
        return dfs(0, true, false);
    }
};
