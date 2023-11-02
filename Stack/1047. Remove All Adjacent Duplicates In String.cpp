/*
1047. Remove All Adjacent Duplicates In String
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    string removeDuplicates(string s) {
        string res = "";
        for(int i = 0; i<s.size(); i++){
            if(!res.empty() && res.back() == s[i]){
                res.pop_back();
                continue;
            }
            else
                res.push_back(s[i]);
        }

        return res;

    }
};
