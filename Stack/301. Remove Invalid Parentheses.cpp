/*
301. Remove Invalid Parentheses
*/


// Backtrack DFS + greedy TC:O(2^n) SC:O(2^n + k) 但因為有去重所以不會到這麼高的時間空間等級 
//此題的去重方式值得學起來
class Solution {
    vector<string> res;
    int maxLen = 0;
public:
    vector<string> removeInvalidParentheses(string s) {
        //先去找出最多需要刪除多少個元素 如果DFS過程中字符串長度超過maxLen那就會是不合法的
        int count = 0; int remove = 0;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == '('){
                count+=1;
            }
            else if(s[i] == ')') count-=1;
            if(count < 0){
                remove+=1;
                count = 0;
            }
        }
        remove+=count;
        maxLen = s.size()-remove;

        string curStr = "";
        DFS(s,0,curStr, 0);
        return res;
    }

    void DFS(string& s, int i, string curStr, int count){
        if(curStr.size() > maxLen) return;
        if(count < 0) return;
        if(i == s.size()) {
            if(count == 0 && curStr.size() == maxLen)
                res.push_back(curStr);
            return;
        }

        if(s[i] != '(' && s[i] != ')'){
            DFS(s,i+1,curStr+s.substr(i,1),count);
        }
        else {
            DFS(s,i+1,curStr+s.substr(i,1), count+(s[i] == '(' ? 1:-1));
            //可以不加入的狀況
            if(curStr.empty() || curStr.back() != s[i]){
                DFS(s,i+1,curStr,count);
            }
        }
    }
};
