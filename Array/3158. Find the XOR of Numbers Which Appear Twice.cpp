/*
3158. Find the XOR of Numbers Which Appear Twice
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int duplicateNumbersXOR(vector<int>& nums) {
        int res = 0;
        unordered_map<int,int> map;
        bool flag = 0;
        for(auto num : nums){
            map[num] += 1;
        }
        for(auto p : map){
            if(p.second == 2 && flag == 0){
                res = p.first;
                flag = 1;
            }
            else if(p.second == 2 && flag == 1){
                res ^= p.first;
            }
        }
        return res;
    }
};
