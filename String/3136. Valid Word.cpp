/*
3136. Valid Word
*/

// TC:O(n) SC:O(3+10)
class Solution {
public:
    bool isValid(string word) {
        int n = word.size();
        if(n < 3) return false;
        unordered_set<char> set = {'@', '#','$'};
        unordered_set<char> set1 = {'a', 'e', 'i', 'o', 'u','A','E','I','O','U'};
        bool countV = 0;
        bool countC = 0;
        for(int i = 0; i < n; i++){
            if(set.find(word[i]) != set.end()) return false;
            if(isdigit(word[i])) continue;
            if(set1.find(word[i]) != set1.end()) {
                countV = true;
            }
            else if((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')){
                countC = true;
            }
        }
        
        if(countC && countV) return true;
        
        return false;
    }
};


/*
至少三個字
一母音 一子因至少
要都是0-9 or 字母
*/
