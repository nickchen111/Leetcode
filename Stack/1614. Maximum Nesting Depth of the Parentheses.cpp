/*
1614. Maximum Nesting Depth of the Parentheses
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int maxDepth(string s) {
        int count = 0;
        int res = 0;
        for(auto x : s){
            if(x == '('){
                res = max(res, ++count);
            }
            else if(x == ')'){
                count -= 1;
            }
        }

        return res;
    }
};
