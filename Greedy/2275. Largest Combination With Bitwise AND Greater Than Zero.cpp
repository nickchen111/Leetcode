/*
2275. Largest Combination With Bitwise AND Greater Than Zero
*/

// TC:O(32*n) SC:O(32)
class Solution {
public:
    int largestCombination(vector<int>& candidates) {
        vector<int> pos(32,0);
        int n = candidates.size();
        for(int i = 0; i < n; i++){
            int num = candidates[i];
            while(num != 0){
                for(int i = 0; i < 32; i++){
                    int cur = 1 & num;
                    if(cur) pos[i] +=1;
                    num = num >> 1;
                }
            }
        }

        int res = 0;
        for(int i = 0; i < 32; i++){
            if(pos[i] > res){
                res = pos[i];
            }
        }

        return res;
    }
};

/*
找出數組內最長的一串subsequence 這串數字做AND 可以大於0
第一個想法 要盡量找到的元素 在我的位置上都要存在 換句話說 先找一個在許多位置上都有東西的數字 or 在某個位置上出現頻率最高的就會是最長答案！？
16 -> 0 0 1 0 0 0 0
17 -> 0 0 1 0 0 0 1 
62 -> 0 1 1 1 1 1 0 
24 -> 0 0 1 1 0 0 0

71 -> 1 0 0 0 1 1 1
*/
