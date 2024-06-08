/*
3174. Clear Digits
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    string clearDigits(string s) {
        int n = s.size();
        stack<int> stack;
        for(int i = 0; i < n; i++){
            if(s[i] >= '0' && s[i] <= '9'){
                if(!stack.empty()){
                    s[stack.top()] = ' ';
                    stack.pop();
                }
                s[i] = ' ';
            }
            else {
                stack.push(i);
            }
        }
        
        string res = "";
        for(int i = 0; i < n; i++){
            if(s[i] != ' ') res += s[i];
        }
        
        return res;
    }
};
