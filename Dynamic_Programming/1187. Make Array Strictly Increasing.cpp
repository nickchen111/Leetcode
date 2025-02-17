// 選or 不選 較好想 TC:O(n * (n + m) * lgm) SC:O(n * (n + m))
class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        ranges::sort(arr2);
        int n = arr1.size();
        vector<unordered_map<int,int>> memo(n);
        auto dfs = [&](auto &&dfs, int i, int pre) -> int {
            if(i < 0) return 0;
            if(memo[i].find(pre) != memo[i].end()) return memo[i][pre];
            int ret = arr1[i] < pre ? dfs(dfs, i-1, arr1[i]) : INT_MAX/2;
            auto iter = lower_bound(arr2.begin(), arr2.end(), pre);
            if(iter != arr2.begin()) {
                ret = min(ret, dfs(dfs, i-1, *--iter) + 1);
            }
            return memo[i][pre] = ret;
        };
        int ans = dfs(dfs, n-1, INT_MAX);
        return ans == INT_MAX/2 ? -1 : ans;
        /*
        算是選or不選的遞推
        // dp : 走到 i 為止 以 arr1[i]結尾 or arr2中選一個更小且滿足條件的數字結尾 可以符合完全嚴格遞增子序列所需操作的次數
        vector<unordered_map<int,int>> dp(n);
        dp[0][arr1[0]] = 0;
        if(arr2[0] < arr1[0]) dp[0][arr2[0]] = 1;
        for(int i = 1; i < n; i++) {
            bool flag = false;
            for(auto &[prevNum, cnt] : dp[i-1]) {
                if(prevNum < arr1[i]) {
                    if(dp[i].count(arr1[i])) dp[i][arr1[i]] = min(dp[i][arr1[i]], cnt);
                    else dp[i][arr1[i]] = dp[i-1][prevNum];
                    flag = true;
                }
                auto iter = upper_bound(arr2.begin(), arr2.end(), prevNum);
                if(iter != arr2.end()) {
                    if(dp[i].count(*iter))
                        dp[i][*iter] = min(dp[i][*iter], cnt + 1);
                    else dp[i][*iter] = cnt + 1;
                    flag = true;
                }
                // cout << prevNum << endl;
            }
            if(!flag) return -1;
        }
        int ans = n;
        for(auto &[num, cnt] : dp[n-1]) {
            ans = min(ans, cnt);
        }
        return ans;
        */
    }
};

// 枚舉選哪個 TC:O(n * (min(n,m) + lgm)) SC:O(n)
class Solution {
public:
    int makeArrayIncreasing(vector<int>& a, vector<int>& b) {
        a.push_back(INT_MAX); // 简化程式碼邏輯
        sort(b.begin(), b.end());
        b.erase(unique(b.begin(), b.end()), b.end()); // 原地去重
        int n = a.size(), memo[n];
        memset(memo, 0, sizeof(memo)); 
        function<int(int)> dfs = [&](int i) -> int {
            int &res = memo[i];
            if (res) return res;
            int k = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
            res = k < i ? INT_MIN : 0;
            if (i && a[i - 1] < a[i])
                res = max(res, dfs(i - 1));
            for (int j = i - 2; j >= i - k - 1 && j >= 0; --j)
                if (b[k - (i - j - 1)] > a[j])
                    // a[j+1] 到 a[i-1] 替换成 b[k-(i-j-1)] 到 b[k-1]
                    res = max(res, dfs(j));
            return ++res; // 把 +1 移到这里，表示 a[i] 不替换
        };
        int ans = dfs(n - 1); // 注意 a 已经添加了一个元素
        return ans < 0 ? -1 : n - ans;
    }
};
