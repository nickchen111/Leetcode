/*
1096. Brace Expansion II
*/


// iterative TC:O(n+nlgn) SC:O(k)
class Solution {
public:
    vector<string> braceExpansionII(string S) {
        string s = "";
        //為了應付 {a,b}c這種情況 會不知道c要幹嘛
        for(int i = 0; i<S.size(); i++){
            if(isalpha(S[i])){
                s.push_back('{');
                s.push_back(S[i]);
                s.push_back('}');
            }
            else s+=S[i];
        }

        stack<unordered_set<string>> Stack;
        stack<int> StackOp;
        unordered_set<string> cur;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == '{'){
                Stack.push(cur);
                StackOp.push(0);
                cur = {};
            }
            else if(s[i] == ','){
                Stack.push(cur);
                StackOp.push(1);
                cur = {};
            }
            else if(s[i] == '}'){
                //逗號可能一次出現很多 他們都算是同層
                while(StackOp.top() == 1){
                    cur = combination(Stack.top(),cur);
                    Stack.pop();
                    StackOp.pop();
                }
                if (StackOp.top() == 0){
                    cur = crossProduct(Stack.top(),cur);
                    Stack.pop();
                    StackOp.pop();
                }
            }
            else if(isalpha(s[i])){
                int j = i+1;
                while(j < s.size() && isalpha(s[j])) j++;
                string tmp = s.substr(i,j-i);
                cur.insert(tmp);
            }
        }
        vector<string> res(cur.begin(),cur.end());
        sort(res.begin(),res.end());
        return res;
    }
    unordered_set<string> combination(unordered_set<string>& a, unordered_set<string>& b){
        unordered_set<string> res; 
        for(auto x:a){
            res.insert(x);
        }
        for(auto x:b){
            res.insert(x);
        }
        return res;
    }
    unordered_set<string> crossProduct(unordered_set<string>& a, unordered_set<string>& b){
        unordered_set<string> res;
        //應付這種情況{a,b} 左邊stack目前是空 要給他一個東西才能跑for迴圈
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


// Recursion   TC:O(n+nlgn) SC:O(k)
class Solution {
public:
    vector<string> braceExpansionII(string s) {
        auto ret = DFS(s,0,s.size()-1);

        vector<string> res;
        for(auto x:ret){
            res.push_back(x);
        }
        sort(res.begin(),res.end());
        return res;
    }
    unordered_set<string> DFS(string& s, int a, int b){
        //"{a,b}c{d,e}f"
        stack<unordered_set<string>> stack;
        unordered_set<string> cur = {};

        for(int i = a; i<=b; i++){
            if(s[i] == '{'){
                int j = i+1;
                int level = 1;
                while(j <=b && level > 0){
                    level+=(s[j] == '{');
                    level-=(s[j] == '}');
                    if(level == 0) break;
                    else
                        j++;
                }
                auto next = DFS(s,i+1,j-1);
                cur = crossProduct(cur,next);
                i = j;
            }
            else if(s[i] == ','){
                stack.push(cur);
                cur = {};
            }
            else {
                int j = i+1;
                while( j<=b && isalpha(s[j])) j++;
                unordered_set<string> next({s.substr(i,j-i)});
                cur = crossProduct(cur,next);
                i = j-1;
            }
        }

        while(!stack.empty()){
            for(auto x:stack.top()){
                cur.insert(x);
            }
            stack.pop();
        }
        return cur;
    }
    unordered_set<string> crossProduct(unordered_set<string>& a, unordered_set<string>& b){
        unordered_set<string> res;
        //應付這種情況{a,b} 左邊stack目前是空 要給他一個東西才能跑for迴圈
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

/*
此題規則 
1. 遇到{}做crossProduct 優先度高
2. 遇到,做 combination
e,{{a},{b}{{c},{d}}},{b}
 0    1   1   0     01  
*/
