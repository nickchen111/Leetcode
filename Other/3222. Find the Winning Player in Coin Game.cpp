/*
3222. Find the Winning Player in Coin Game
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    string losingPlayer(int x, int y) {
        bool flag = 0;
        while(x >= 1 && y >= 4){
            x -= 1;
            y -= 4;
            flag = 1 - flag;
        }
        
        if(flag) return "Alice";
        else return "Bob";
    }
};

/*
115 -> 1x + 4y
*/
