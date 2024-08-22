/*
476. Number Complement
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int findComplement(int num) {
        string s;
        while(num != 0){
            int cur = num & 1;
            s += cur + '0';
            num >>= 1;
        }
        int res = 0;
        int count = 0;
        for(int i = 0; i < s.size(); i++){
            int cur = 1 - (s[i]-'0');
            res += (cur << count);
            count += 1;
        }

        return res;
    }
};
