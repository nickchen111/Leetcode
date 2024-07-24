/*
2191. Sort the Jumbled Numbers
*/

// TC:O(nlgn + n*10) SC:O(n)
class Solution {
public:
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        vector<int> map(10);
        for(int i = 0; i < mapping.size(); i++){
            map[i] = mapping[i];
        }
        int n = nums.size();
        vector<int> res(n);
        vector<pair<int,int>> arr;
        for(int i = 0; i < n; i++){
            string s = to_string(nums[i]);
            int cur = 0;
            for(int j = 0; j < s.size(); j++){
                cur = cur*10 + map[s[j]-'0'];
            }
            arr.push_back({cur,i});
        }

        sort(arr.begin(), arr.end());
        for(int i = 0; i < arr.size(); i++){
            res[i] = nums[arr[i].second];
        }

        return res;
    }
};
