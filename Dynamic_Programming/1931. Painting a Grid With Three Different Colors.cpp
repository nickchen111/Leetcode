/*
1931. Painting a Grid With Three Different Colors
*/

// TC:O(n * 3^m + 2 * 3^m) SC:O(3^m)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int colorTheGrid(int m, int n) {
        // 3^5 * 1000 * 3^5 會TLE 需要預處理
        LL space = pow(3,m);
        auto self = [&](int state) -> bool {
            vector<int> arr(m);
            for(int i = 0; i < m; i++) {
                arr[i] = state % 3;
                state /= 3;
            }

            for(int i = 1; i < m; i++) {
                if(arr[i] == arr[i-1]) return false;
            } 

            return true;
        };
        auto cross = [&](int state1, int state2) -> bool {
            vector<int> arr1(m);
            vector<int> arr2(m);
            for(int i = 0; i < m; i++) {
                arr1[i] = state1 % 3;
                state1 /= 3;
                arr2[i] = state2 % 3;
                state2 /= 3;
            }
            for(int i = 0; i < m; i++) {
                if(arr1[i] == arr2[i]) return false;
            }
            return true;
        };
        vector<bool> check(space, false);
        // vector<vector<LL>> dp(n, vector<LL>(space)); // 1000 : 3^5
        vector<LL> dp(space);
        for(int i = 0; i < space; i++) {
            if(self(i)) dp[i] = 1;
            else check[i] = true;
        }
        unordered_map<int, unordered_set<int>> map;
        for(int i = 0; i < space; i++) {
            if(check[i]) continue;
            for(int j = 0; j < space; j++) {
                if(check[j]) continue;
                if(cross(i, j)) {
                    map[i].insert(j);
                }
            }
        }
        for(int i = 1; i < n; i++) {
            auto dp_tmp = dp;
            for(int j = 0; j < space; j++) {
                dp[j] = 0;
                if(check[j]) continue;
                for(auto &k : map[j]) {
                    dp[j] = (dp[j] + dp_tmp[k]) % MOD;
                }
            }
        }

        LL res = 0;
        for(int j = 0; j < space; j++) {
            res = (res + dp[j]) % MOD;
        }

        return res;
    }
};
