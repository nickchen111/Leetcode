/*
1945. Sum of Digits of String After Convert
*/


// TC:O(nk) SC:O(10n)
class Solution {
public:
    int getLucky(string s, int k) {
        string str;
        for(int i = 0; i < s.size(); i++){
            str += to_string(s[i]-'a'+1);
        }

        while(k--){
            int n = str.size();
            int sum = 0;
            for(int i = 0; i < n; i++){
                sum += (str[i]-'0');
            }
            str = to_string(sum);
        }

        return stoi(str);
    }
};
