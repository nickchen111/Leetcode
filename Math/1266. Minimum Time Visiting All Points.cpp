/*
1266. Minimum Time Visiting All Points
*/

// TC:O(n) SC:O(1)
class Solution {
    int toTime(vector<int>& a, vector<int>& b){
        int xdiff = abs(a[0]-b[0]);
        int ydiff= abs(a[1]-b[1]);

        return max(xdiff, ydiff);
    }
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        //此題數學題要求將所有線連一起的一筆到位的線之最短距離 其實從哪點開始都是一樣的
        int res = 0;
        for(int i = 1; i< points.size(); i++){
            res += toTime(points[i-1],points[i]);
        }

        return res;
    }
};
