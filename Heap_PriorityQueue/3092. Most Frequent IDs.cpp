/*
3092. Most Frequent IDs
*/

// TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
        unordered_map<int,LL> map; // 數字->freq
        multiset<LL> set;
        
        int n = freq.size();
        vector<LL> res(n);
        for(int i = 0; i < n; i++){
            if(freq[i] > 0){
                if(map[nums[i]] != 0) set.erase(set.find(map[nums[i]]));
                map[nums[i]] += freq[i];
                set.insert(map[nums[i]]);
            }
            else {
               
                map[nums[i]] += freq[i];
                if(map[nums[i]] > 0){
                    set.erase(set.find(map[nums[i]]-freq[i]));
                    set.insert(map[nums[i]]);
                } 
                
                if(map[nums[i]] == 0){
                    set.erase(set.find(map[nums[i]]-freq[i]));
                    map.erase(nums[i]);
                } 
            }
            
            if(set.size() > 0){
                res[i] = *set.rbegin();
            }
        }
        
        return res;
    }
};

/*
每次都會新增or 刪除元素 問說當前在數組內頻率最高的頻率為多少
*/
