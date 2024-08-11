/*
3248. Snake in Matrix
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int finalPositionOfSnake(int n, vector<string>& commands) {
        int x = 0;
        int y = 0;
        for(auto str : commands){
            if(str == "UP"){
                x -= 1;
            }
            else if(str == "DOWN"){
                x += 1;
            }
            else if(str == "LEFT"){
                y -= 1;
            }
            else if(str == "RIGHT"){
                y += 1;
            }
        }
        
        return x*n+y;
    }
};
