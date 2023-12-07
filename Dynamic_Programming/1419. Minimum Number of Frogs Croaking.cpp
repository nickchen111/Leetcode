/*
1419. Minimum Number of Frogs Croaking
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        int n = croakOfFrogs.size();
        int c = 0, r = 0, o = 0, a = 0, k = 0;
        int res = 0;
        for(auto ch : croakOfFrogs){
            if(ch == 'c'){
                c++;
            }
            else if(ch == 'r'){
                c--;
                r++;
                if(c < 0) return -1;
            }
            else if(ch == 'o'){
                r--;
                o++;
                if(r < 0) return -1;
            }
            else if(ch == 'a'){
                o--;
                a++;
                if(o < 0) return -1;
            }
            else if(ch == 'k'){
                a--;
                if(a < 0) return -1;
            }
            res = max(res, c + r + o + a + k);
        }
        if(c > 0 || r > 0 || o > 0 || a > 0) return -1;//代表沒叫完
        return res;
    }
};

/*
此題說一個青蛙叫完croak 才能接著叫
問最少需要幾隻青蛙叫完給定字串
叫到k的時候上一個有o的狀態-1
叫到c的時候如果前面青蛙沒叫完就要新的青蛙叫 
叫到roak的時候如果前面沒有相對應的字母 return -1
*/
