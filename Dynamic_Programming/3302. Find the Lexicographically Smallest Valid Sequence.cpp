/*
3302. Find the Lexicographically Smallest Valid Sequence
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<int> suffix(n+1);
        suffix[n] = m;
        for(int i = n-1, j = m-1; i >= 0; i--){
            if(j >= 0 && word1[i] == word2[j]) {
                j--;
            }
            
            suffix[i] = j + 1; // 完全比對成功後 word1 與 word2 最長後綴起始下標位置
        }
        
        
        vector<int> res(m);
        bool changed = false;
        for(int i = 0, j = 0; i < n; i++){
            if(word1[i] == word2[j] || !changed && suffix[i+1] <= j+1){
                if(word1[i] != word2[j]){
                    changed = true;
                }
                
                res[j] = i;
                j++;
                
                if(j == m) return res;
            }
        }
        
        return {};
        
    }
};
