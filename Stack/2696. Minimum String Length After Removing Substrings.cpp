/*
2696. Minimum String Length After Removing Substrings
*/

//TC:O(n) SC:O(1)
class Solution {
public:
    int minLength(string s) {
        int n = s.size();
        string res;
        for(int i = 0; i < n; i++){
            res += s[i];
            if(res.size() >= 2){
                int m = res.size();
                if(res.substr(m-2) == "AB" || res.substr(m-2) == "CD"){
                    res.pop_back();
                    res.pop_back();
                } 
            }
        }

        return (int)res.size();
        
    }
};
