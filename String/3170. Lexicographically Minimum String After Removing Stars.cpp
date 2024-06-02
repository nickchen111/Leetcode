/*
3170. Lexicographically Minimum String After Removing Stars
*/

// TC:O(26*n) SC:O(26*n)
class Solution {
public:
    string clearStars(string s) {
        int n = s.size();
        vector<vector<int>> count(26);
        for(int i = 0; i < n; i++){
            if(s[i] != '*'){
                count[s[i]-'a'].push_back(i);
            }
            else {
               
                int idx = -1;
                for(int j = 0; j < 26; j++){
                    if(count[j].size() > 0){
                        idx = j;
                        break;
                    }
                }
                if(idx != -1){
                    int idx2 = count[idx].back();
                    s[idx2] = ' ';
                    count[idx].pop_back();
                }
                
                s[i] = ' ';
            }
        }
        
        string res;
        for(int i = 0; i < n; i++){
            if(s[i] != ' ') res += s[i];
        }
        
        return res;
    }
};
