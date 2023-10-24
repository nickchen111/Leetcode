/*
224. Basic Calculator
*/

//TC:O(n) SC:O(n)
class Solution {
public:
    int calculate(string s) {
        string S = "+";
        //讓每個數字前面都會有+-號之類的
        for(auto ch:s){
            if(ch == ' ') continue;//把空的去掉
            S+=ch;
            if(ch == '(') S+= "+";
        }
        s = S;

        int sign, sum = 0;
        stack<int> nums;
        stack<int> signs;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == '+' || s[i] == '-'){
                sign = s[i]=='+'?1:-1;
            }

            else if(isdigit(s[i])){
                int j = i;
                while(j < s.size() && isdigit(s[j])) j++;
                int num = stoi(s.substr(i,j-i));
                i = j-1;//否則下一次的迴圈會漏掉一個
                sum += num*sign;//sumu就是這一圈的總和
            }

            else if(s[i] == '('){
                nums.push(sum);
                signs.push(sign);
                sum = 0;//讓他重新計算下一圈的總和
            }
            else if(s[i] == ')'){
                sum = sum*signs.top() + nums.top();
                nums.pop();
                signs.pop();
            }
        }
        return sum;
    }
};

//參照III的程式碼
class Solution {
public:
    int calculate(string s) 
    {
        stack<string>Stack;
        string curStr;
        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='(')
            {
                Stack.push(curStr);
                curStr = "";
            }
            else if (s[i]==')')
            {                
                int curRes = eval(curStr);
                curStr = Stack.top() + to_string(curRes);
                Stack.pop();                
            }
            else
                curStr.push_back(s[i]);
        }
        return eval(curStr);        
    }
    
    int eval(string s)
    {
        string S = "+";
        for (auto ch:s)
        {
            if (ch==' ') continue;
            S.push_back(ch);
            if (ch=='(')
                S+="+";
        }
        s = S;
        
        
        vector<long>nums;

        for (int i=0; i<s.size(); i++)
        {
            if (s[i]=='+' || s[i]=='-')
            {
                int j = i+1;
                //加了這項判斷才可以通過 +-(-2)這種case 不然在stol的時候會有問題
                if(s[j]=='+' || s[j]=='-') j++;
                if(s[j] == '-'){
                    s = s.substr(j+1);
                    s.insert(s.begin(),'+');
                } 

                while (j<s.size() && isdigit(s[j]))
                    j++;
                long num = stol(s.substr(i+1,j-i-1));
                if (s[i]=='+') nums.push_back(num);
                else if (s[i]=='-') nums.push_back(-num);
                i = j-1;
            }
            else if (s[i]=='*' || s[i]=='/')
            {
                int j = i+1;
                if (s[j]=='+' || s[j]=='-') j++;
                while (j<s.size() && isdigit(s[j]))
                    j++;
                int num = stoi(s.substr(i+1,j-i-1));                
                if (s[i]=='*') nums.back() *= num;
                else if (s[i]=='/') nums.back() /= num;
                i = j-1;
            }
        }

        int ret = 0;
        for (int i=0; i<nums.size(); i++)
            ret+=nums[i];
        return ret;
    }
    
    
};
/*
括號的題目 
可以用遞迴也可以用stack維護
考點
1.將所有正負數一律用加法處理 
2. 判斷遇到 左括號右括號要進棧退棧
*/
