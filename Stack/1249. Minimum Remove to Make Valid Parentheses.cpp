/*
1249. Minimum Remove to Make Valid Parentheses
*/


// Stack結合貪心思想的考題 TC:O(n) SC:O(n)
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        //跟301差不多 但這題只要求一個結果 所以用stack記錄不合法的將他置為空 之後再來處理即可
        stack<int> stack;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == ')'){
                if(stack.empty()){
                    s[i] = ' ';
                }
                else stack.pop();
            }
            else if(s[i] == '(')
                stack.push(i);
        }

        while(!stack.empty()){
            s[stack.top()] = ' ';
            stack.pop();
        }

        string res;
        for(auto ch:s){
            if(ch != ' ') res+=ch;
        }

        return res;
    }
};
