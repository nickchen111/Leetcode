/*
1106. Parsing A Boolean Expression
*/

// TC:O(n) SC:O(n) iterative 
class Solution {
public:
    bool parseBoolExpr(string s) {
        stack<vector<int>> stack;
        std::stack<char> stackOp;
        vector<int> nums;
        int res;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == '|' || s[i] == '&' || s[i] == '!'){
                stackOp.push(s[i]);
                stack.push(nums);
                nums = {};
            }
            else if(s[i] == ')'){
                res = eval(nums,stackOp.top());
                stackOp.pop();
                // new val = stack.top() + num;
                nums = stack.top();
                nums.push_back(res);
                stack.pop();
            }
            else if(s[i] == 't' || s[i] == 'f'){
                nums.push_back(s[i] == 't');
            }
        }
        return res;
    }
    int eval(vector<int>& nums, char ch){
        int res;
        if(ch == '!'){
            res = !nums[0];
        }
        else if(ch == '|'){
            res = 0;
            for(auto x:nums){
                res |= x;
            }
        }
        else if(ch == '&'){
            res = 1;
            for(auto x:nums){
                res &=x;
            }
        }
        return res;
    }
};

//Recursion
class Solution {
public:
    bool parseBoolExpr(string s) {
        bool res =  helper(s,0,s.size()-1);
        return res;
    }
    bool helper(string& s, int a, int b){
        
        vector<int> val;
        //直接跳過最前面的操作符跟最後面的)
        for(int i = a+2; i<=b-1; i++){
            if (s[i]=='&' || s[i]=='|' || s[i]=='!'){
                int level = 1;
                int j = i+2;
                while( j <=b-1 && level > 0){
                    level+=(s[j] == '(');
                    level-=(s[j] == ')');
                    if(level == 0) break;
                    else j++;
                }
                val.push_back(helper(s,i,j));
                i = j;
            }
            else if(s[i] == 't' || s[i] == 'f'){
                val.push_back(s[i] == 't');
            }
        }
        return eval(val, s[a]);
    }
    int eval(vector<int>& nums, char ch){
        int res;
        if(ch == '!'){
            res = !nums[0];
        }
        else if(ch == '|'){
            res = 0;
            for(auto x:nums){
                res |= x;
            }
        }
        else if(ch == '&'){
            res = 1;
            for(auto x:nums){
                res &=x;
            }
        }
        return res;
    }
};
