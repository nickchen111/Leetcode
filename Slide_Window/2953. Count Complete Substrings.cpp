/*
2953. Count Complete Substrings
*/

// TC:O(26*26*n) SC:O(26*n)
class Solution {
    int GetC(char c){
        return c-'a';
    }
    int solve(string& s, int k){
        int n = s.size();
        vector<vector<int>> count(n, vector<int>(26,0));//紀錄在每個長度的時候每個字出現的次數
        int res = 0;
        for(int i = 0; i < n; i++){
            for(int c = 0; c < 26; c++){
                count[i][c] = (i ? count[i-1][c]:0);
            }
            
            count[i][GetC(s[i])]+=1;
            //計算可能會有的字母種類就可以得知要求的長度
            for(int numc = 1; numc <= 26; numc++){
                int j = i-numc*k+1;
                if(j < 0) break;
                bool flag = 1;
                for(int c = 0; c < 26; c++){
                    int countc = count[i][c]- (j > 0 ? count[j-1][c]:0);
                    if(countc != 0 && countc != k){
                        flag = 0;
                        break;
                    }
                }
                if(flag) res++;
            }
        }
        
        return res;
    }
public:
    int countCompleteSubstrings(string word, int k) {
        int n = word.size();
        int i = 0;
        vector<string> candidate;
        while(i < n){
            string cur;
            int j = i;
            cur.push_back(word[i]);
            while( j+1 < n && abs(GetC(word[j+1])-GetC(word[j])) <= 2){
                j++;
                cur.push_back(word[j]);
            }
            
            candidate.push_back(cur);
            i = j+1;
        }
        
        int res = 0;
        for(auto &s:candidate){
            res+=solve(s,k);
        }
        
        return res;
    }
};
