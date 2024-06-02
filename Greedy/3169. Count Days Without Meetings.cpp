/*
3169. Count Days Without Meetings
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            if(a[0] != b[0]) return a[0] < b[0];
            else return a[1] > b[1];
        };
        sort(meetings.begin(), meetings.end(), cmp);
        int n = meetings.size();
        int res = meetings[0][0] - 1;
        int maxDay = meetings[0][1];
        for(int i = 0; i < n; i++){
            int j = i;
            int end = meetings[i][1];
            while(j < n && end >= meetings[j][0]){
                end = max(end, meetings[j][1]);
                maxDay = max(maxDay, end);
                j++;
            }
            
            if(j != n){
                res += meetings[j][0] - end - 1;
            }
            i = j-1;
        }
        
        res += days - maxDay;
        
        return res;
    }
};
