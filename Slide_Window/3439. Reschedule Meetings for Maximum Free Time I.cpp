// TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        int n = startTime.size(), i = 0;
        LL sum = 0, ans = 0;
        for(int j = 0; j < n; j++) {
            sum += (LL)(endTime[j] - startTime[j]);
            if(j - i + 1 == k) {
                // 可以知道當前的最前面 跟最後面的拼圖 兩者相減就是當前有的範圍
                int start = i - 1 < 0 ? 0 : endTime[i-1];
                int end = j + 1 >= n ? eventTime : startTime[j+1];
                // cout << start << ' ' << end << ' ' << sum << endl;
                ans = max(ans, end - start - sum);
                sum -= (LL)(endTime[i] - startTime[i]);
                i+= 1;
            }
        }
        return ans;
        
    }
};

/*
可以移動 startTime 讓連續的free time盡量多
應該是滑窗
移動時考慮後面的那個是啥 是有東西就是他的起點 沒東西就是evetTime 也就是 eventTime - 當前的終點
*/
