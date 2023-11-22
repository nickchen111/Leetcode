/*
2516. Take K of Each Character From Left and Right
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int takeCharacters(string s, int k) {
        int A = 0; int B = 0; int C = 0;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == 'a') A+=1;
            else if(s[i] == 'b') B+=1;
            else if(s[i] == 'c') C+=1;
        }
        if(A < k || B < k || C < k) return -1;

        A = A-k; B = B-k; C = C-k;
        int res = 0;
        int n = s.size();
        int j = 0;
        int countA = 0; int countB = 0; int countC = 0;
        for(int i = 0; i<s.size(); i++){
            while(countA <= A && countB <= B && countC <= C){
                res = max(res,j-i);
                if(j == n) break;
                if(s[j] == 'a') countA+=1;
                else if(s[j] == 'b') countB+=1;
                else if(s[j] == 'c') countC+=1;
                j++;
            }
            if(s[i] == 'a') countA-=1;
            else if(s[i] == 'b') countB-=1;
            else if(s[i] == 'c') countC-=1;
        }

        return n-res;
    }
};
/*
每一次都能從最前或者最後拿數字 return最少需要拿幾次 才能拿到a b c三種各字數量k個
在條件滿足的狀況下中間最長的window可以多寬 中間的windo必定滿足 每個字的總數目-K >= count 
此題變相在問一個區間限制次數的話最長會是多少
*/
