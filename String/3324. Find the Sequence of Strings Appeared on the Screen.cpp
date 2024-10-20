/*
3324. Find the Sequence of Strings Appeared on the Screen
*/

// TC:O(26*n) SC:O(26*n)
class Solution {
public:
    vector<string> stringSequence(string target) {
        int n = target.size();
        vector<string> res;
        string s;
        for(int i = 0; i < n; i++) {
            while(s.size() < i+1) {
                s += 'a';
                res.push_back(s);
            }
            
            while(s.back() != target[i]) {
                s.back() += 1;
                res.push_back(s);
            }
        }
        
        return res;
    }
};
