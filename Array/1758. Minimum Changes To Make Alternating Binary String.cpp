/*
1758. Minimum Changes To Make Alternating Binary String
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minOperations(string s) {
        int res = 0;
        int n = s.size();

        for(int i = 0; i < n; i++){
            if(s[i]-'0' != i % 2){
                res+=1;
            }
        }

        return min(res,n-res);
    }
};
