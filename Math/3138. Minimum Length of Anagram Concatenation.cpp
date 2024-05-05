/*
3138. Minimum Length of Anagram Concatenation
*/


// TC:O(n) SC:O(26)
class Solution {
public:
    int minAnagramLength(string s) {
        vector<int> count(26,0);
        int n = s.size();
        for(int i = 0; i < n; i++){
            count[s[i]-'a']  += 1;
        }
        
        int res = n;
        int target = 0;
        int idx = -1;
        for(int i = 0; i < n; i++){
            if(count[i] != 0){
                target = count[i];
                idx = i;
                break;
            } 
        }
        for(int i = idx+1; i < 26; i++){
            if(count[i] != 0){
                target = gcd(target, count[i]);
            }
        }
        
        res = n /target;
        
        return res;
    }
};

/*
求出所有用過的字母的最大公因數

*/
