/*
772. Basic Calculator III🔒
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int calculate(string s) {
        stack<string> Stack;
        string curStr;
        for(int i = 0; i<s.size(); i++){
            //某一圈的剛開始將之前的裝進stack
            if(s[i] == '('){
                Stack.push(curStr);
                curStr = "";
            }
            //某一圈的結束 將之先做好計算再與之前的結合
            else if(s[i] == ')'){
                int curRes = eval(curStr);
                curStr = Stack.top() + to_string(curRes);
                Stack.pop(); 
            }
            else curStr.push_back(s[i]);
        }

        return eval(curStr);
    }

    //處理沒有括號的狀況
    int eval(string s){
        string S = "+";
        for(auto ch:s){
            if(ch ==' ') continue;
            S+=ch;
        }
        s = S;

        vector<long> nums;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '+' || s[i] == '-'){
                int j = i+1;
                if(s[j] == '+' || s[j] == '-') j++;
                while(j<s.size() && isdigit(s[j])){
                    j++;
                }
                long num = stol(s.substr(i+1,j-i-1));
                if(s[i] == '+') nums.push_back(num);
                else if(s[i] == '-') nums.push_back(-num);
                i = j-1;
            }

            else if(s[i] == '*' || s[i] == '/'){
                int j = i+1;
                if(s[j] == '+' || s[j] == '-') j++;
                while(j<s.size() && isdigit(s[j])){
                    j++;
                }
                long num = stol(s.substr(i+1,j-i-1));
                if(s[i] == '*') nums.back()*=num;
                else if(s[i] == '/') nums.back()/=num;
                i = j-1;
            }
        }
        int res = 0;
        for(auto x:nums){
            res+=x;
        }

        return res;
    }
};

/*
特別需要注意一些極端狀況
+5--4*-3++3/+5
*/
