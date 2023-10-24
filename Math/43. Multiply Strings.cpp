/*
43. Multiply Strings
*/

//TC:O(m*n) SC:O(m+n) 
class Solution {
public:
    string multiply(string num1, string num2) {
        int m = num1.size(); int n = num2.size();
        vector<int> res(m+n);
        
        for(int i = m-1; i>=0; i--){
            for(int j = n-1; j>=0; j--){
                int x = num1[i] - '0';
                int y = num2[j] - '0';

                int pos1 = i+j;
                int pos2 = i+j+1;

                int sum = x*y + res[pos1]*10 + res[pos2];
                res[pos1] = sum/10;
                res[pos2] = sum%10;
            }
        }
        string ans;
        for(int i = 0; i < res.size(); i++){
            if(ans.size() == 0 && res[i] == 0) continue;//可能結果中最高位為0 or 結果真的就是0
            ans += (res[i]+'0');
        }
        if(ans.size() == 0) return "0";

        return ans;
    }
};

/*
此題算是字符串的數學題
關鍵在於理解 兩個index 之間的相乘 
高位在:i+j
低位在:i+j+1
xxxxxxx
高。   低
然後做一些edge case判斷
*/
