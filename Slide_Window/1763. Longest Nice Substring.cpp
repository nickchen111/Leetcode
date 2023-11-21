/*
1763. Longest Nice Substring
*/


// TC:O(26*n^2) SC:O(52)
class Solution {
public:
    string longestNiceSubstring(string s) {
        //小寫減大寫等於32
        vector<int> low(26),up(26);
        int n = s.size();
        int maxLen = 0;
        string res;
        for(int i= 0; i<n; i++){
            string tmp;
            for(int j = i; j<n; j++){
                if(s[j] >= 'a') low[s[j]-'a']+=1;
                else up[s[j]-'A']+=1;
                tmp+=s[j];
                bool ok = true;
                for(int k = 0; k<26; k++){
                    if(low[k] > 0 && up[k] == 0) ok = false;
                    if(up[k] > 0 && low[k] == 0) ok = false;
                }
                if(ok){
                    if(j-i+1 > maxLen){
                        maxLen = j-i+1;
                        res = tmp;
                    }
                }
            }
            low.assign(26,0);
            up.assign(26,0);
        }

        return res;

    }
};
