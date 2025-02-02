// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        int n = startTime.size();
        // vector<LL> prefix(n); // 在 i之前與最大的洞是多大?
        vector<LL> suffix(n);
        // for(int i = 1; i < n; i++) {
        //     prefix[i] = max(prefix[i-1], (LL)startTime[i-1] - (i-2 >= 0 ? endTime[i-2] : 0));
        // }
        for(int i = n-2; i >= 0; i--) {
            suffix[i] = max(suffix[i+1], (LL)(i+2 < n ? startTime[i+2] : eventTime) - endTime[i+1]);
        }
        LL sum = 0, ans = 0, prefix = 0;
        int i = 0;
        for(int j = 0; j < n; j++) {
            sum += (LL)(endTime[j] - startTime[j]);
            if(j - i + 1 == 1) {
                // 可以知道當前的最前面 跟最後面的拼圖 兩者相減就是當前有的範圍
                int start = i - 1 < 0 ? 0 : endTime[i-1];
                int end = j + 1 >= n ? eventTime : startTime[j+1];
                // cout << start << ' ' << end << ' ' << sum << endl;
                // if(prefix[i] >= sum || suffix[j] >= sum) ans = max(ans, (LL)end - start);
                if(prefix >= sum || suffix[j] >= sum) ans = max(ans, (LL)end - start);
                else ans = max(ans, (LL)end - start - sum);
                sum -= (LL)(endTime[i] - startTime[i]);
                i+= 1;
            }
            prefix = max(prefix, (LL)startTime[i-1] - (i-2 >= 0 ? endTime[i-2] : 0));
        }
        return ans;
    }
};
