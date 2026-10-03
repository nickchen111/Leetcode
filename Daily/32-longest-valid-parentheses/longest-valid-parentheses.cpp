class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        stack<int> stack;
        
        int res = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == ')'){
                if(!stack.empty() && s[stack.top()] == '('){
                    stack.pop();
                    res = max(res, i - (stack.empty() ? -1:stack.top()));
                }  
                else stack.push(i);
            }
            else if(s[i] == '('){
                stack.push(i);
            }
            
        }

        return res;
    }
};

/*
求符合括號規則的最長substring
() or (()) or ()()
如果stackempty但是遇到) 直接忽略
每次讓stack變空的時候都更新一下最大值
還要紀錄上個狀態有多少個
()()() (())
*/