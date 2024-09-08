/*
3280. Convert Date to Binary
*/

// TC:O(32*n) SC:O(m)
class Solution {
public:
    string convertDateToBinary(string date) {
        string res;
        int n = date.size();
        for(int i = 0; i < n; i++){
            int j = i;
            string cur;
            string tmp;
            while(j < n && date[j] != '-') {
                cur += date[j];
                j++;
            }
            int num = stoll(cur);
            while(num != 0){
                if(num & 1){
                    tmp = '1' + tmp;
                }
                else tmp = '0' + tmp;
                num /= 2;
            }
            tmp += '-';
            res += tmp;
            i = j;
        }
        res.pop_back();
        
        return res;
    }
};
