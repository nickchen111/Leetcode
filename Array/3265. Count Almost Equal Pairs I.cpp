/*
3265. Count Almost Equal Pairs I
*/


// TC:O(n * U ) U最大是7!/2! 也就是C7取2 然後再乘上7 SC:O(n) 
class Solution {
public:
    int countPairs(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        sort(nums.begin(), nums.end());
        // 枚舉右邊 維護左邊 紀錄左邊有出現過哪些
        unordered_map<int,int> map;
        for(int i = 0; i < n; i++){
            unordered_set<int> set;
            set.insert(nums[i]);
            string s = to_string(nums[i]);
            int m = s.size();
            for(int j = 0; j < m; j++){
                for(int k = j + 1; k < m; k++){
                    swap(s[j], s[k]);
                    set.insert(stoi(s));
                    swap(s[j], s[k]);
                }
            }
            for(auto x : set){
                res += map[x];
            }
            map[nums[i]] ++;
        }
        
        return res;
    }
};
