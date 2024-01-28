/*
3021. Alice and Bob Playing Flower Game
*/

// TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long flowerGame(int n, int m) {
        if(m == 0 && n == 0) return 0;
        
        LL count = 0;
        for(int i = 1; i <= n; i++){
            if(i % 2 == 0){
                if(m % 2 == 0) count += m/2;
                else count += m/2+1;
            }
            else {
                count += m/2;
            }
        }
        
        return count;
    }
};

/*
總之就是最後取完所有花的獲勝 但是給你兩個大小 要你算可能的花總和
花總和必須是奇數 就贏了有多少種可能配對
if(n == 0偶數) m = 1, 3, 5, 7...假設m為 偶數 4 -> 4/2 -> 1,3 奇數: 5, 1,3, -> 5/2+1
if(n == 1奇數) m 就必須選偶數 m = 4-> 0,2,4 -> 4/2+1 , 奇數:5, 0,2,4 -> 5/2+1
*/
