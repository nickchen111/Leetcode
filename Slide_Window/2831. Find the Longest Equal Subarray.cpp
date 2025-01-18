/*
2831. Find the Longest Equal Subarray
*/

// 2025.01.18 兩種寫法 一種存位置 一種存距離之差value
class Solution {
public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> mp(n+1);
        for(int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }
        int res = 1;
        for(int t = 1; t <= n; t++) {
            int i = 0, sum = 0;
            for(int j = 1; j < mp[t].size(); j++) {
                // x O x x x x O
                sum += j - 1 < i ? 0 : (mp[t][j] - mp[t][j-1] - 1);
                while(sum > k) {
                    sum -= (mp[t][i+1] - mp[t][i] - 1);
                    i += 1;
                }
                res = max(res, j - i + 1);
            }
        }
        return res;
    }
};

class Solution {
public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> mp(n+1);
        for(int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i - mp[nums[i]].size());
        }
        int res = 1;
        for(int t = 1; t <= n; t++) {
            int i = 0;
            for(int j = 1; j < mp[t].size(); j++) {
                // x O x x x x O
                while(mp[t][j] - mp[t][i] > k) {
                    i += 1;
                }
                res = max(res, j - i + 1);
            }
        }
        return res;
    }
};

// Map TC:O(n) SC:O(n)
class Solution {
public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, vector<int>> mp;
        for(int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }
        int res = 1;
        for(auto [num, arr] : mp) {
            int i = 0, sum = 0;
            for(int j = 1; j < arr.size(); j++) {
                // x O x x x x O
                sum += j - 1 < i ? 0 : (arr[j] - arr[j-1] - 1);
                while(sum > k) {
                    sum -= (arr[i+1] - arr[i] - 1);
                    i += 1;
                }
                res = max(res, j - i + 1);
            }
        }
        return res;
    }
};

/*
紀錄每個數字的idx 排序頻率 從idx開始跳
[x x [2 x x 2 x x] x 2 x x x x 2]
pos[j]-pos[i]+1 -(j-i+1) <= K
                合法的數量
*/
