/*
357. Count Numbers with Unique Digits
*/

// DP TC:O(1024*n*10) SC:O(1024*n)
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n == 0) return 1;
        int num = pow(10,n)-1;
        string s = to_string(num);
        int m = s.size();
        vector<vector<int>> memo(m, vector<int>(1<<10, -1));
        function<int(int i, int mask, bool isLimit, bool isNum)> dfs = [&](int i, int mask, bool isLimit, bool isNum) -> int {
            if(i == m) return isNum;
            if(!isLimit && memo[i][mask] != -1) return memo[i][mask];
            int res = 0;
            if(!isNum) res = dfs(i+1, mask, false, false);
            int up = isLimit ? s[i]-'0' : 9;
            for(int j = 1 - (isNum); j <= up; j++) {
                if(((mask >> j) & 1)) continue;
                res += dfs(i+1, mask | (1 << j), isLimit && j==up, true);
            }

            if(!isLimit) memo[i][mask] = res;
            return res;
        };

        return dfs(0, 0, true, false) + 1;
    }
};

// TC:O(n^2) SC:O(1)
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        int res = 1; // 因為這題需要包含 0
        for(int len = 1; len <= n; len++){
            res += A(10,len) - A(9,len-1);
        }

        return res;
    }
    int A(int m, int n){
        int count = 1;
        for(int i = 0; i < n; i++){
            count *= (m-i);
        }

        return count;
    }
};

/*
就去看每個長度上 可以組成多少種組合 但不能有leading zero的狀況下
*/
