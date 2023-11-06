/*
13. Roman to Integer
*/


//TC:O(n) SC:O(n)
class Solution {
public:
    int romanToInt(string s) {
        map<char, int> m{{'I', 1}, {'V', 5},
                         {'X', 10}, {'L', 50},
                         {'C', 100}, {'D',500}, {'M', 1000}};
        
        char p = 0;
        int ans = 0;
        for(char c:s){
            ans += m[c];
            if(p && m[c] > m[p])
            ans -= 2*m[p];
            p = c;
        }
        return ans;
    }
};

