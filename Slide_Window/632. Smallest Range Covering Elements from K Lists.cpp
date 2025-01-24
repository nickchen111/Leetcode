// TC:O(LlgL) SC:O(L) L 為所有數字加總長度
class Solution {
    using LL = long long;
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int n = nums.size();
        vector<pair<LL,int>> arr;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < nums[i].size(); j++) {
                arr.push_back({nums[i][j], i});
            }
        }
        std::sort(arr.begin(), arr.end());
        int i = 0;
        vector<int> cnt(n);
        int valid = 0, start = -1e5, end = 1e5+1;
        for(int j = 0; j < arr.size(); j++) {
            if(cnt[arr[j].second] == 0) valid += 1;
            cnt[arr[j].second] += 1;
            while(valid == n) {
                if(end - start > arr[j].first - arr[i].first) {
                    end = arr[j].first, start = arr[i].first;
                }
                if(cnt[arr[i].second] == 1) valid -= 1;
                cnt[arr[i++].second] -= 1;
            }
        }
        return {start, end};
    }
};
