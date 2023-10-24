/*
452. Minimum Number of Arrows to Burst Balloons
*/

class Solution {
    static bool comp(vector<int>& a, vector<int>& b){
        return a[1]<b[1];
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), comp);
        int i = 0;
        int count = 0;
        while(i < points.size()){
            int j = i+1;
            count++;
            while(j < points.size() && points[j][0] <= points[i][1]){
                j++;
            }
            i = j;
        }

        return count;
    }
};
/*
與題目435一樣寫法 雖然寫法一致但目的不同 
*/
