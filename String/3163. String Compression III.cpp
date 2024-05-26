/*
3163. String Compression III
*/

// TCC:O(n) SC:O(1)
class Solution {
public:
    string compressedString(string word) {
        string res;
        int n = word.size();
        int count = 1;
        for(int i = 1; i < n; i++){
            if(word[i] == word[i-1] && count < 9){
                count += 1;
            }
            else if(word[i] == word[i-1]){
                res += to_string(count) + word[i-1];
                count = 1;
            }
            else if(word[i] != word[i-1]){
                res += to_string(count) + word[i-1];
                count = 1;
            }
        }
        
        res += to_string(count) + word.back();
        
        return res;
    }
};
