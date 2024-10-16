/*
539. Minimum Time Difference
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        vector<int> minutes;
        for (const string& time : timePoints) {
            int hour = stoi(time.substr(0, 2));
            int minute = stoi(time.substr(3, 2));
            minutes.push_back(hour * 60 + minute);
        }
        
        sort(minutes.begin(), minutes.end());
        
        int minDiff = INT_MAX;
        int n = minutes.size();
        
        for (int i = 1; i < n; i++) {
            minDiff = min(minDiff, minutes[i] - minutes[i-1]);
        }
        
        // Compare last and first time (circular)
        minDiff = min(minDiff, 1440 + minutes[0] - minutes[n-1]);
        
        return minDiff;
    }
};
