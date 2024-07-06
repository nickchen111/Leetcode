/*
2582. Pass the Pillow
*/

// TC:O(1) SC:O(1)
class Solution {
public:
    int passThePillow(int n, int time) {
        int mod = (time/(n-1)) % 2;
        if(mod == 0){
            return (time%(n-1)) + 1;
        }
        else {
            return n - (time%(n-1));
        }
    }
};

/*
1 0 10 20 30
2 1 9 11 19 21 29 31
3 2 8 12 18 22 28 32
4 3 7 13 17 23 27 33
5 4 6 14 16 24 26 34
6 5 15 25 35
時間 / 人數-1 % 2 == 0 代表在正向輪 == 1 代表在負向輪
*/
