/*
20. Valid Parentheses
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool isValid(string s) {
        stack<int> Stack;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
                Stack.push(i);
            }
            else if(s[i] == ')'){
                if(!Stack.empty() && s[Stack.top()] == '('){
                    Stack.pop();
                }
                else return false;
            } 

            else if(s[i] == ']'){
                if(!Stack.empty() && s[Stack.top()] == '['){
                    Stack.pop();
                }
                else return false;
            } 

            else if(s[i] == '}'){
                if(!Stack.empty() && s[Stack.top()] == '{'){
                    Stack.pop();
                }
                else return false;
            } 
        }

        return Stack.size() == 0 ? true:false;
    }
};
