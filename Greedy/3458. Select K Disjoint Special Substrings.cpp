// TC:O(n + U*n + mlgm + m)  U 為字母數量，m為區間數量 SC:O(m + U)
class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        if(k == 0) return true;
        
        int n = s.size();
        vector<int> first(26,-1);
        vector<int> last(26);
        vector<pair<int,int>> intervals; // 求兩個不重疊的最多區塊是多少個
        for(int i = 0; i < n; i++) {
            if(first[s[i] - 'a'] == -1) first[s[i] - 'a'] = i;
            last[s[i] - 'a'] = i;
        }
        for(int ch = 0; ch < 26; ch++) {
            if(first[ch] == -1) continue;
            int end = last[ch];
            bool flag = true;
            for(int j = first[ch]; j <= end; j++) {
                int f = first[s[j] - 'a'];
                end = max(end, last[s[j] - 'a']);
                if(f < first[ch]) {
                    flag = false;
                    break;
                }
            }
            if(flag && end - first[ch] + 1 != n) {
                intervals.emplace_back(first[ch], end);
            }
        }
        n = intervals.size();
        if(n == 0) return false;
        
        auto cmp = [&](const pair<int,int>& a, const pair<int,int>& b) {
            if(a.second != b.second) return a.second < b.second;
            return a.first < b.first;
        };
        sort(intervals.begin(),intervals.end(),cmp);

        int count = 0;
        int i = 0;
        while(i < n){
            count += 1;
            int j = i+1;
            while(j < intervals.size() && intervals[j].first <= intervals[i].second){
                j++;
            }
            i = j;
        }
        
        return count >= k;
    }
};
