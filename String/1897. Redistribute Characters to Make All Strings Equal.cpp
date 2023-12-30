/*
1897. Redistribute Characters to Make All Strings Equal
*/

// TC:O(n) SC:O(26)
class Solution {
public:
    bool makeEqual(vector<string>& words) {
        int n = words.size();
        if(n == 1) return true;
        vector<int> count(26,0);
        for(auto &word : words){
            for(auto &ch : word){
                count[ch-'a'] += 1;
            }
        }

        for(auto &x : count){
            if(x % n != 0) return false;
        }

        return true;
    }
};
