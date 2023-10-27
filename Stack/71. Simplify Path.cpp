/*
71. Simplify Path
*/

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
