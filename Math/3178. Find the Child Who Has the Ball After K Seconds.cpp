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

class Solution {
public:
    int numberOfChild(int n, int k) {
        
        if((k/(n-1))%2) return n-1-(k%(n-1));
        else return k%(n-1);
        
    }
};

/*
第k秒是哪個小孩拿著球
n = 3 
第一個人為 0 -> 4 -> 8 ....
k <= 1
k / (n-1) 會知道他在第幾輪
%2 就知道是正著還是逆著過程 正個就給他 n - 1 - r 逆著就是r
如果是正著過去的話 (k/(n-1))%2 == 0  答案n-1-r r為餘數
反過來的話就會是r
*/
