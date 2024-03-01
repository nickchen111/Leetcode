/*
2864. Maximum Odd Binary Number
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    string maximumOddBinaryNumber(string s) {
        int count = 0;
        int n = s.size();
        for(int i = 0; i < n; i++){
            if(s[i] == '1') count += 1;
        }
        string res;
        while(count > 1){
            res += "1";
            count -= 1;
        }
        while(res.size() < n-1){
            res += "0";
        }
        res += "1";

        return res;
    }
};
