/*
726. Number of Atoms
*/

// TC:O(n) SC:O(k) k為化學元素的種類
class Solution {
public:
    string countOfAtoms(string formula) {
        stack<map<string,int>> stack;
        map<string, int> cur;

        for(int i= 0; i<formula.size(); i++){
            if(formula[i] == '('){
                stack.push(cur);
                cur.clear();
            }
            else if(formula[i] == ')'){
                int j = i+1;
                while(j < formula.size() && isdigit(formula[j])) j++;
                int num;
                if(j == i+1) num = 1;
                else num = stoi(formula.substr(i+1,j-i-1));
                for(auto x:cur){
                    cur[x.first] = cur[x.first]*num;
                }
                for(auto x:stack.top()){
                    cur[x.first]+=x.second;
                }
                stack.pop();
                i = j-1;

            }
            else if(formula[i] <= 'Z' && formula[i] >= 'A'){
                int j = i+1;
                while(j < formula.size() && formula[j] <= 'z' && formula[j] >= 'a') j++;
                string element = formula.substr(i,j-i);
                i = j-1;//到字母最後一位
                while(j < formula.size() && isdigit(formula[j])) j++;
                int num;
                if(j == i+1) num = 1;
                else num = stoi(formula.substr(i+1,j-i-1));
                cur[element] += num;
                i = j-1;
            }
        }
        
        string res;
        for(auto x:cur){
            res+=x.first;
            if(x.second > 1)
                res+=to_string(x.second);
        }
        return res;
    }
};
