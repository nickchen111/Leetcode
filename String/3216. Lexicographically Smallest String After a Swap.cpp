/*
3216. Lexicographically Smallest String After a Swap
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    string getSmallestString(string s) {
        int n = s.size();
        for(int i = 1; i < n; i++){
            if((((s[i]-'0') % 2) == ((s[i-1]-'0') % 2)) && s[i]-'0' < s[i-1]-'0'){
                swap(s[i], s[i-1]);
                break;
            }
        }
        
        return s;
    }
};
