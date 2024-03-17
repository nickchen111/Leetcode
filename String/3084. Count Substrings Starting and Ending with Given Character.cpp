/*
3084. Count Substrings Starting and Ending with Given Character
*/

// TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long countSubstrings(string s, char c) {
        LL res = 0;
        int n = s.size();
        LL count = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == c){
                count += 1;
            }
        }
        
        res = res + count*(count-1)/(LL)2;
        res = res + count;
        
        return res;
    }
};


// 隨意c3取2 + 單讀取
