/*
1190. Reverse Substrings Between Each Pair of Parentheses
*/

//TC:O(n^2) SC:O(n)
class Solution {
public:
    string reverseParentheses(string s) {
        string res;
        int n = s.size();
        stack<int> stack;
        
        for(int i = 0; i < n; i++){
            if(s[i] == '('){
                stack.push(res.size());
            }
            else if(s[i] == ')'){
                int j = stack.top();
                stack.pop();
                reverse(res.begin() + j, res.end());
            }
            else res += s[i];
        }
        
        return res;
    }
};
