/*
150. Evaluate Reverse Polish Notation
*/

//TC:O(n) SC:O(n)
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> Stack;
        for(auto s:tokens){
            if(s == "+"||s == "-" ||s == "*" ||s == "/"){
                int b = Stack.top();
                Stack.pop();
                int a = Stack.top();
                Stack.pop();
                if(s == "+"){
                    Stack.push(a+b);
                }
                else if(s == "-"){
                    Stack.push(a-b);
                }
                else if(s == "*"){
                    Stack.push(a*b);
                }
                else if(s == "/"){
                    Stack.push(a/b);
                }
            }
            else{
                Stack.push(stoi(s));
            }
        }
        return Stack.top();
    }
};
/*
此題為著名的逆波蘭表達式
發明出來就是為了計算機方便用棧進行運算
*/
