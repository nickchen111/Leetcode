class Solution {
public:
    vector<string> braceExpansionII(string S) {
        string s = "";
        for(int i = 0; i < S.size(); i++){
            if(isalpha(S[i])){
                s += '{';
                s += S[i];
                s += '}';
            }
            else s += S[i];
        }

        int n = s.size();
        stack<set<string>> Stack;
        stack<int> StackOp;
        set<string> cur;
        
        for(int i = 0; i < n; i++){
            //因為左括號入棧的話 等等就要用交集
            if(s[i] == '{'){
                Stack.push(cur);
                StackOp.push(0);
                cur.clear();
            }
            else if(s[i] == ','){
                Stack.push(cur);
                StackOp.push(1);
                cur.clear();
            }
            else if(s[i] == '}'){
                //逗號都要先處理完
                while(StackOp.top() == 1){
                    cur = combination(Stack.top(), cur);
                    Stack.pop();
                    StackOp.pop();
                }
                if(StackOp.top() == 0) {
                    cur = crossProduct(Stack.top(), cur);
                    Stack.pop();
                    StackOp.pop();
                }
            }
            else if(isalpha(s[i])){
                int j = i + 1;
                while(j < n && isalpha(s[j])) j++;
                string tmp = s.substr(i,j-i);
                cur.insert(tmp);
            }
        }
        
        vector<string> res(cur.begin(), cur.end());

        return res;
    }

    set<string> combination(set<string>& a, set<string>& b){
        set<string> res; 
        for(auto x:a){
            res.insert(x);
        }
        for(auto x:b){
            res.insert(x);
        }
        return res;
    }

    set<string> crossProduct(set<string>& a, set<string>& b){
        set<string> res;
        if(a.size() == 0) a.insert("");
        if(b.size() == 0) b.insert("");//雖然b不會是空
        for(auto x:a){
            for(auto y:b){
                res.insert(x+y);
            }
        }
        return res;
    }
};