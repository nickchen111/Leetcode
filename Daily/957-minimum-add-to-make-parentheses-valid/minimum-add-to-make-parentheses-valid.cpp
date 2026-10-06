class Solution {
public:
    int minAddToMakeValid(string s) {
        int n = s.size();
        int count = 0;
        int res = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == '(') count ++;
            else {
                if(count) count  -= 1;
                else res += 1;
            }
        }

        return res + count;
    }
};