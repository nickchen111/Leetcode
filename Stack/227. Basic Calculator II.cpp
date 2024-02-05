/*
227. Basic Calculator II
*/


// 2/5 
class Solution {
public:
    int calculate(string s) {

        while(s[0] == ' ') s = s.substr(1);
        string S = s[0] == '-' ? "-" : "+";

        for(auto ch:s){
            if(ch == ' ') continue;
            S+=ch;
        }
        s = S;

        int n = s.size();
        int sum = 0;
        int sign;
        stack<int> num;
        for(int i = 0; i < n; i++){
            if(s[i] == '+' || s[i] == '-'){
                sign = s[i] == '+' ? 1 : -1;
                int j = i+1;
                while(j < n && isdigit(s[j])) j++;
                int temp = stoi(s.substr(i+1, j-i-1));
                temp*=sign;
                num.push(temp);
                i = j - 1;

            }
            else if(s[i] == '*' || s[i] == '/'){
                int j = i+1;
                while(j < n && isdigit(s[j])) j++;
                int temp = stoi(s.substr(i+1, j-i-1));
                int cur = s[i] == '*' ? num.top()*temp : num.top() / temp;
                num.pop();
                num.push(cur);
                i = j - 1;
            }
        }

        int res = 0;
        while(!num.empty()){
            res += num.top();
            num.pop();
        }

        return res;
    }
};

//TC:O(n) SC:O(n)
class Solution {
public:
    int calculate(string s) {
        string S = "+";
        for(auto ch:s){
            if(ch == ' ') continue;
            S+=ch;
        }
        s = S;

        stack<int> nums;
        int sum = 0;
        int sign;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '+' || s[i] == '-'){
                sign = s[i] == '+' ? 1:-1;
                int j = i+1;
                while(j < s.size() && isdigit(s[j])){
                    j++;
                }
                int num = stoi(s.substr(i+1,j-i-1));
                sum = num*sign;
                nums.push(sum);
                i = j-1;
            }
            else if(!nums.empty() && s[i] == '*' || s[i] == '/'){
                
                int j = i+1;
                while(j < s.size() && isdigit(s[j])){
                    j++;
                }
                int num = stoi(s.substr(i+1,j-i-1));

                num = s[i] == '*' ? nums.top()*num:nums.top()/num;
                nums.pop();
                nums.push(num);
                i = j-1;
            }
        }

        int res = 0;
        while(!nums.empty()){
            res+=nums.top();
            nums.pop();
        }

        return res;
    }
};
/*
跟 I 的差別是這題沒有括號 但是可能會有乘除法的狀況
此題可以不用stack結構 用一般vector即可 因為沒有括號的狀況
*/
