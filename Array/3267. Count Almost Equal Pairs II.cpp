/*
3267. Count Almost Equal Pairs II
*/


// TC:O(n * U ) U最大是7!/4! 也就是C7取4 然後再乘上7 SC:O(n) 
class Solution {
public:
    int countPairs(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        sort(nums.begin(), nums.end());
        // 枚舉右邊 維護左邊 紀錄左邊有出現過哪些
        unordered_map<int,int> map;
        for(int i = 0; i < n; i++){
            string s = to_string(nums[i]);
            unordered_set<int> set = {nums[i]};
            for(int j = 0; j < s.size(); j++){
                for(int k = j + 1; k < s.size(); k++){
                    swap(s[j], s[k]);
                    set.insert(stoi(s));
                    for(int p = j + 1; p < s.size(); p++){
                        for(int q = p + 1; q < s.size(); q++){
                            swap(s[p], s[q]);
                            set.insert(stoi(s));
                            swap(s[p], s[q]);
                        }
                    }
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
