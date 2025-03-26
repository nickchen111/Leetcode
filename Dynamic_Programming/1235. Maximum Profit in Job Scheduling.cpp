/*
1235. Maximum Profit in Job Scheduling
*/


// 2025.01.05 TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        
        int n = startTime.size();
        vector<LL> dp(n+1);
        vector<array<LL, 3>> arr;
        for(int i = 0; i < n; i++) {
            arr.push_back({endTime[i], startTime[i], profit[i]});
        }
        auto cmp = [](const array<LL, 3>& a, const array<LL, 3>& b) {
            if(a[0] != b[0]) return a[0] < b[0];
            return a[1] < b[1];
        };
        sort(arr.begin(), arr.end(), cmp);
        for(int i = 0; i < n; i++) {
            LL start = arr[i][1], end = arr[i][0], benefit = arr[i][2];
            int j = upper_bound(arr.begin(), arr.begin() + i, array<LL, 3>{start, LLONG_MAX}) - arr.begin(); // 如果是.begin(), .begin() + 0會是搜索空區間，返回begin()
            dp[i+1] = max(dp[i], dp[j] + benefit);
        }

        return dp[n];
    }
};

// TC:O(nlgU) 這裡的Ｕ會是該start ~ end 的最大值SC:O(n)
class Solution {
    using LL = long long;
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        map<LL, LL> dp;
        dp[0] = 0;
        int n = startTime.size();
        vector<vector<int>> arr;
        for(int i = 0; i < n; i++) {
            arr.push_back({startTime[i], endTime[i], profit[i]});
        }
        auto cmp = [](const vector<int>& a, const vector<int>& b) {
            if(a[1] != b[1]) return a[1] < b[1];
            return a[0] < b[0];
        };
        sort(arr.begin(), arr.end(), cmp);
        for(int i = 0; i < n; i++) {
            LL start = arr[i][0], end = arr[i][1], benefit = arr[i][2];
            auto iter = dp.upper_bound(start);
            iter = prev(iter);
            dp[end] = max(res, iter->second + benefit);
        }

        return dp.rbegin()->second;
    }
};

/*
求每個不重疊區間裡面的數值加總 哪些加總起來profit最大
每個區間如果都去找跟他不重疊的 取最大值 就會是答案
每到一個新的事件終點他都去看以他的為起點搜尋 每個在他之前的終點與他的start不重疊的 選一個最大的加上去
代表前面等同於要維護一個單調遞增的序列
如果dp定義成 dp[t] : by the time of t, the maximum profit i可取可不取
這樣dp[t] = max(dp[t-1], 二分出的dp[j] + val[t]);
此題在構思的時候還是要去思考435題的求最多區間構築出不重複的區間 non-overlapping
這題的dp定義也很像Kadane 概念截止到i為止符合條件的最大值 不一定要是包含ｉ本身可以是他前面的區間
*/
