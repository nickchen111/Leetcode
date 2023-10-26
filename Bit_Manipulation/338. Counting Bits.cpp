/*
338. Counting Bits
*/

//TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> countBits(int n) {
        // i & (-i) 可以保留最後一位的1 ex: (110 & -110) -> 10
        vector<int> res(n+1,0);
        
        for(int i = 1; i<=n; i++){
            res[i] = res[i & (i-1)]+1;//+1就是把去掉的1加回來 前面那項操作類似DP
        }

        return res;
    }
};
