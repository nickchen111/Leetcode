/*
2301. Match Substring After Replacement
*/

// Brute force: TC:O(n^2) SC:O(k)
class Solution {
    bool table[256][256];
public:
    bool matchReplacement(string s, string sub, vector<vector<char>>& mappings) {
        //Brute force
        for(auto p:mappings){
            table[p[0]][p[1]] =1;
        }

        for(int i = 0; i<s.size(); i++){
            //逐個去判斷整個s是否有合法開頭
            int flag = 1;
            for(int j = 0; j<sub.size(); j++){
                if(i+j< s.size() && s[i+j] == sub[j] || table[sub[j]][s[i+j]]) continue;
                flag = 0;
                break;
            }
            if(flag) return true;
        }

        return false;
    }
};
