/*
1578. Minimum Time to Make Rope Colorful
*/

// TC:O(n) SC:O(1) 簡潔寫法 帶著最大值candidate往後走
class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = colors.size();
        int res = 0;
        for(int i = 1; i < n; i++){
            if(colors[i] == colors[i-1]){
                res += min(neededTime[i-1], neededTime[i]);
                neededTime[i] = max(neededTime[i-1], neededTime[i]);
            }
        }

        return res;
    }
};


// TC:O(n) SC:O(1)
class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int n = colors.size();
        colors.push_back('#');
        int count = 1;
        int res = 0;
        int sum = 0;
        int maxVal = 0;
        for(int i = 1; i <= n; i++){
            if(colors[i] == colors[i-1]){
                count++;
                sum += neededTime[i-1];
                maxVal = max(maxVal, neededTime[i-1]);
            }
            else {
                if(count > 1){
                    sum += neededTime[i-1];
                    maxVal = max(maxVal, neededTime[i-1]);
                    res += (sum - maxVal);
                    count = 1;
                    sum = 0;
                    maxVal = 0;
                }
            }
        }

        return res;
    }
};

/*
此題說有一堆氣球綁好排成一排 愛麗絲小鬼不希望氣球顏色連續的排序 想讓包伯倒霉鬼去拆掉一些氣球
每個氣球拆除的時間有一個數組 問倒霉鬼最少需要多少時間達成小鬼的要求
此題做法目前想到的是先確定一段連續的氣球 然後找最少數值的n-1個 去掉 就可以move on下一區間
*/
