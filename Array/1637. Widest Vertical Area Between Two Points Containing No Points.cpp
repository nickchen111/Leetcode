/*
1637. Widest Vertical Area Between Two Points Containing No Points
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        sort(points.begin(), points.end());

        int res = 0;
        for(int i = 1; i < points.size(); i++){
            res = max(res, points[i][0] - points[i-1][0]);
        }

        return res;
    }
};

/*
找出最寬的面積 y軸就不管了看x軸
*/
