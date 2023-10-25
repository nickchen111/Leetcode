/*
66. Plus One
*/

//TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        int carry = 1;
        int i = n-1;
        vector<int> res;
        while(i >= 0 || carry){
            int val = carry;
            if(i >= 0) val +=digits[i];
            carry = val/10;
            val%=10;
            res.insert(res.begin(),val);
            i--;
        }

        return res;
    }
};
