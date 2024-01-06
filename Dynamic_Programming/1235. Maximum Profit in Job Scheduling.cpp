/*
1235. Maximum Profit in Job Scheduling
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = endTime.size();
        vector<vector<int>> job;
        for(int i = 0; i < n; i++){
            job.push_back({startTime[i],endTime[i],profit[i]});
        }
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            return a[1] < b[1];
        };

        sort(job.begin(), job.end(), cmp);
        
        vector<pair<int,int>> dp; // endTIme->val
        int res = 0;
        for(int i = 0; i < n; i++){
            int cur = res;
            auto iter = upper_bound(dp.begin(), dp.end(), make_pair(job[i][0], INT_MAX));
            if(iter != dp.begin())
                cur = max(cur, prev(iter)->second + job[i][2]);
            else cur = max(cur, job[i][2]);
            dp.push_back({job[i][1], cur});
            res = max(res, cur);
        }

        
        return res;
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
