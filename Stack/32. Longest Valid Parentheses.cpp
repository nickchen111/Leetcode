/*
32. Longest Valid Parentheses
*/


// stack TC:O(n) SC:O(1)
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> Stack;
        int res = 0;

        for(int i = 0; i<s.size(); i++){
            if(s[i] == '('){
                Stack.push(i);
            }
            else{
                if(!Stack.empty() && s[Stack.top()] == '('){
                    Stack.pop();
                    res = max(res, i -( Stack.empty() ? -1:Stack.top()));
                }

                else {
                    Stack.push(i);
                }
            }
        }

        return res;
    }
};

/*
用stack來做
此題要想到三種情況
1.完全暢通無阻 大家都是合法的
((()))
2. 中間遇到 之前已經談出棧的狀況 要將之前的結果也納入長度加總
(**** (()) 中間的*代表合法被退棧的
3.加入的右括號沒人跟他匹配 他之後無論如何都無法合法
) ((()))
*/
