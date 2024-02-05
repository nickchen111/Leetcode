/*
772. Basic Calculator III🔒
*/

// 2/5
class Solution {
public:
    int calculate(string s) {
       
        // 切割字串變成沒括號的狀態
        int n = s.size();
        stack<string> stack; // 124 + 345 + 234 + ...
        string cur = "";
        

        for(int i = 0; i < n; i++){
            if(s[i] == '('){
                stack.push(cur);
                cur = "";
            }
            else if(s[i] == ')'){
                int num = eval(cur);
                cur = stack.top() + to_string(num);
                stack.pop();
            }
            else cur.push_back(s[i]);
        }

        return eval(cur);
    }

    int eval(string& s){
       
        string S;
        int n = s.size();
        // 1-
        for(int i = 0; i < n; i++){
            if(s[i] == ' ') continue;
            S += s[i];
        }
        s = S;
        if(s[0] != '-') s = "+" + s;
        
        n = s.size();
        int sign;
        stack<int> stack;
        for(int i = 0; i < n; i++){
            if(s[i] == '+' || s[i] == '-'){
                sign = s[i] == '+' ? 1 : -1;
                int j = i + 1;
                while(j < n && !isdigit(s[j])) j++;
                while(j < n && isdigit(s[j])) j++;
                
                int num = stoi(s.substr(i+1, j-i-1));
                stack.push(num*sign);
                i = j - 1;
            }
            else if(s[i] == '*' || s[i] == '/'){
                int j = i + 1;
                while(j < n && !isdigit(s[j])) j++;
                while(j < n && isdigit(s[j])) j++;
               
                int num = stoi(s.substr(i+1, j-i-1));
                int cur = stack.top();
                cur = s[i] == '*' ? (cur*num) : (cur/num);
                stack.pop();
                stack.push(cur);
                i = j - 1;
            }
        }

        int res = 0;
        while(!stack.empty()){
            res += stack.top();
            stack.pop();
        }

        return res;
    }
};


// 遇到左括號 將當前資料放入stack 迎接美好的新未來 keep going 右括號暫停
// +(1+(4+5+2)-3)+(6+8)

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
