class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = colors.size(), i = 0, ans = 0;
        while(i < n) {
            int sum = neededTime[i], mx = neededTime[i];
            while(i + 1 < n && colors[i] == colors[i+1]) {
                mx = max(mx, neededTime[i+1]);
                sum += neededTime[i+1];
                i ++;
            }
            ans += sum - mx;
            i ++;
        }
        return ans;
    }
};