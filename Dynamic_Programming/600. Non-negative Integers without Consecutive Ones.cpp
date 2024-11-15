/*
600. Non-negative Integers without Consecutive Ones
*/

// TC:O(2*2*n) SC:O(2*n)
class Solution {
public:
    int findIntegers(int n) {
        string s = format("{:b}", n); // 可以直接把整數轉二進制 但需要支援C++20 或者可以用 s = bitset<32>(n).to_string(), 再把前導零去掉 s.erase(0, s.find_first_not_of('0'))
        
        // while(n) {
        //     s += (n&1) + '0';
        //     n >>= 1;
        // }
        // reverse(s.begin(), s.end());
        int m = s.size();
        vector<vector<int>> memo(m, vector<int>(2, -1));
        function<int(int i, bool isLimit, bool isOne)> dfs = [&](int i, bool isLimit, bool isOne) -> int {
            if(i == m) return 1;
            int res = 0;
            if(!isLimit && memo[i][isOne] != -1) return memo[i][isOne];
            if(isOne) res = dfs(i+1, isLimit && s[i] == '0', false);
            else {
                int up = isLimit ? s[i]-'0' : 1;
                for(int j = 0; j <= up; j++) {
                    res += dfs(i+1, isLimit && j == up, j == 1);
                }
            }

            if(!isLimit) memo[i][isOne] = res;
            return res;
        };
        return dfs(0, true, false);
    }
};
