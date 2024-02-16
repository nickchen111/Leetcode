/*
1481. Least Number of Unique Integers after K Removals
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        int n = arr.size();
        unordered_map<int,int> map;
        for(auto ch : arr){
            map[ch] += 1;
        }
        vector<int> nums;
        for(auto p : map){
            nums.push_back(p.second);
        }

        sort(nums.begin() , nums.end());
        int count = 0;
        int res = 0;
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] + count <= k){
                count += nums[i];
                res += 1;
            }
            else break;
        }

        return (int)nums.size() - res;

    }
};
