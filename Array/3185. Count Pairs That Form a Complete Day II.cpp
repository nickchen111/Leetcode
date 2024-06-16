/*
3185. Count Pairs That Form a Complete Day II
*/

// TC:O(n) SC:O(24)
class Solution {
    using LL = long long;
public:
    long long countCompleteDayPairs(vector<int>& hours) {
        int n = hours.size();
        unordered_map<LL, LL> map;
        LL res = 0;
        for(int i = 0; i < n; i++){
            LL need = (24 - (hours[i] % 24)) % 24;
            LL mod = (hours[i] % 24);
            if(map.find(need) != map.end()){
                res += map[need];
            }
            
            map[mod] += 1;
        }
        
        return res;
    }
};
