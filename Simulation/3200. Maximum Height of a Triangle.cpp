/*
3200. Maximum Height of a Triangle
*/

// TC:O(100) SC:O(1)
class Solution {
public:
    int maxHeightOfTriangle(int red, int blue) {
        int count1 = 0;
        int count2 = 0;
        int flag1=  -1;
        int flag2 = -1;
        int red1 = red;
        int blue1 = blue;
        int red2 =  red;
        int blue2 = blue;
        for(int i = 1; i <= 100; i++){
            if(red1 >= i && (flag1 == -1 || flag1 == 1)){
                count1 ++;
                flag1 = 0;
                red1 -= i;
            }
            else if(blue1 >= i && (flag1 == 0)){
                flag1 = 1;
                count1 += 1;
                blue1 -= i;
            }
            
            if(blue2 >= i && (flag2 == -1 || flag2 == 0)){
                count2 ++;
                flag2 = 1;
                blue2 -= i;
            }
            else if(red2 >= i && (flag2 == 1)){
                flag2 = 0;
                count2 += 1;
                red2 -= i;
            }
            
            
        }
        
        return max(count2, count1);
    }
};
