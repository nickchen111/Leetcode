/*
2054. Two Best Non-Overlapping Events
*/


// Map TC:O(nlgn) SC:O(n)
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
        //如果數字end比我靠後數字又小 可以直接不理他
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

// vector TC:O(nlgn) SC:O(n)
class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            if(a[1] != b[1]){
                return a[1] < b[1];
            }
            else return a[0] < b[0];
        };
        sort(events.begin(), events.end(), cmp);
        vector<pair<int,int>> dp;// endTime -> val;
        dp.push_back({0,0});
        int res = 0;
        int maxVal = 0;
        for(auto event : events){
            int start = event[0], end = event[1], val = event[2];
            auto iter = lower_bound(dp.begin(), dp.end(), make_pair(start, INT_MIN));
            iter = prev(iter);
            res = max(res, iter->second + val);
            maxVal = max(maxVal, val);
            dp.push_back({end,maxVal});
        }

        return res;
    }
};

/*
每個區間如果都去找跟他不重疊的 取最大值 就會是答案
每到一個新的事件起點他都去看以他為起點 每個在他之前的終點與他的start不重疊的 選一個最大的加上去
代表前面等同於要維護一個單調遞增的序列
如果dp定義成 dp[t] : by the time of t, the maximum profit i可取可不取
這樣dp[t] = max(dp[t-1], 二分出的dp[j] + val[t]);
此題在構思的時候還是要去思考435題的求最少區間構築出不重複的區間
*/
