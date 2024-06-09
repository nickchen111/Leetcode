/*
3178. Find the Child Who Has the Ball After K Seconds
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int numberOfChild(int n, int k) {
        int cur = 0;
        bool flag = 1;
        for(int i = 1; i <= k; i++){
            if(flag){
                cur++;
                if(cur == n-1){
                    flag = 0;
                }
            }
            else {
                cur --;
                if(cur == 0){
                    flag = 1;
                }
            }
        }
        
        return cur;
        
    }
};
