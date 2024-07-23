/*
1636. Sort Array by Increasing Frequency
*/

// TC:O(ngln) SC:O(n)
class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        unordered_map<int,int> map;
        for(auto x : nums){
            map[x] += 1;
        }
        vector<pair<int,int>> arr;
        for(auto p : map){
            arr.push_back({p.second, p.first});
        }
        auto cmp = [](const pair<int,int>& a, const pair<int,int>& b){
            if(a.first != b.first){
                return a.first < b.first;
            }
            else return a.second > b.second;
        };
        sort(arr.begin(), arr.end(), cmp);
        vector<int> res;
        for(auto &[freq, num] : arr){
            for(int i = 0; i < freq; i++){
                res.push_back(num);
            }
        }

        return res;
    }
};
