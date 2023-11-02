/*
71. Simplify Path
*/

// TC:O(n) SC:O(n) 11/2
class Solution {
public:
    string simplifyPath(string path) {
        stack<string> s;
        string res;
        for(int i = 0; i<path.size(); i++){
            if(path[i] == '/') continue;
            string temp;
            while(i < path.size() && path[i] != '/'){
                temp+=path[i];
                i++;
            }

            if(temp == ".."){
                if(!s.empty()){
                    s.pop();
                }
                else continue;
            }

            else if(temp == ".") continue;

            else s.push(temp);
        }

        while(!s.empty()){
            res = "/" + s.top() + res;
            s.pop();
        }

        if(res.size() == 0) return "/";
        return res;
    }
};

// TC:O(n) SC:O(n)
class Solution {
public:
    string simplifyPath(string path) {
        //遇到..去掉上個目錄 (返回) 一個.不管他 問最後的路徑長什麼樣
        int i = 1;
        vector<string> split;
        while(i < path.size()){
            int j = path.find("/",i);
            if(j == -1){
                split.push_back(path.substr(i));
                break;
            }
            else{
                split.push_back(path.substr(i,j-i));
            }
            i = j+1;
        }
        
        vector<string> res;
        for(int i = 0; i<split.size(); i++){
            if(split[i] == "." || split[i] == "") continue;
            else if(split[i] == ".."){
                if(!res.empty()){
                    res.pop_back();
                }
                else continue;
            }
            else res.push_back(split[i]);
        }

        string ret = "";
        for(auto s:res){
            ret+="/"+s;
        }

        return ret.empty() ? "/":ret;
    }
};
