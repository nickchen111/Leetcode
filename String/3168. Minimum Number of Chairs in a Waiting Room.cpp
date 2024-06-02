/*
3168. Minimum Number of Chairs in a Waiting Room
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minimumChairs(string s) {
        int count = 0;
        int res = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == 'E'){
                count += 1;
            }
            else count -= 1;
            res = max(res, count);
        }
        
        return res;
    }
};
