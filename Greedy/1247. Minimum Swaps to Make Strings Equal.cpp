/*
1247. Minimum Swaps to Make Strings Equal
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int minimumSwap(string s1, string s2) {
        int n = s1.size();
        
        int res = 0;
        int count_x = 0, count_y = 0;
        for(int i = 0; i < n; i++){
            if(s1[i] != s2[i]){
                if(s1[i] == 'x') count_x++;
                else count_y++;
            }
        }

        //必須是一對一對的才能消掉 否則像ex3 xx xy -> 1 個 x就消不掉
        if((count_x + count_y)%2 == 1) return -1;

        // case1
        res += (count_x/2) + (count_y/2);
        // case2
        if(count_x % 2 == 1 || count_y % 2 == 1) res += 2;

        return res;
    }
};

/*
此題題意為兩個字串 只由x y 組成 兩個字串任何idx上的位置可以互換 問最少要換多少次讓兩個字串相同
1. 看ex 看起來要成功必須兩個字串組成比例相同
case 1 :
x x 
y y 
case 2 :
x y
y x
*/
