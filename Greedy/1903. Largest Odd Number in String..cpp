/*
1903. Largest Odd Number in String
*/

//TC:O(n) SC:O(1)
class Solution {
public:
    string largestOddNumber(string num) {
        int len = -1;
        int n = num.size();
        for(int i = n-1; i >= 0; i--){
          int nums = num[i]-'0';
            if(nums % 2 == 1){
                len = i + 1;
                break;
            }
        }
        if(len == -1) return "";
        else return num.substr(0,len);
    }
};
