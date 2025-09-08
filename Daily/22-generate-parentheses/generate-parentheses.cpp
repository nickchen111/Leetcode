class Solution {

public:
    vector<string> generateParenthesis(int n) {
        //用stack
        vector<string> res;
        backtrack(n,n,"",res);
        return res;
    }

    void backtrack(int left, int right,string cur, vector<string>& res){
        if(left == 0 && right == 0){
            res.push_back(cur);
            return;
        }
        if(left > right) return;
        if(left < 0 || right < 0) return;
        cur.push_back('(');
        backtrack(left-1,right,cur,res);
        cur.pop_back();

        cur.push_back(')');
        backtrack(left,right-1,cur,res);
        cur.pop_back();
    }
};