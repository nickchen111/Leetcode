/*
3047. Find the Largest Area of Square Inside Two Rectangles
*/

// TC:O(nlgn+n^2) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        int n = bottomLeft.size();
        LL res = 0;
        for(int i = 0; i < n; i++){
            bottomLeft[i].push_back(topRight[i][0]);
            bottomLeft[i].push_back(topRight[i][1]);
        }
        sort(bottomLeft.begin(), bottomLeft.end());
        for(int i = 0; i < n; i++){
            int bottom_x = bottomLeft[i][0], bottom_y = bottomLeft[i][1], top_x = bottomLeft[i][2], top_y = bottomLeft[i][3];
            for(int j = i + 1; j < n; j++){
                
                int bottom_max_x = max(bottomLeft[j][0], bottom_x);
                int bottom_max_y = max(bottomLeft[j][1], bottom_y);
                int top_min_x = min(bottomLeft[j][2], top_x);
                int top_min_y = min(bottomLeft[j][3], top_y);
                LL side;
                side = min(top_min_x - bottom_max_x, top_min_y - bottom_max_y);
                if(side <= 0) continue;
                else res = max(res, side*side);
            }
        }
        
        return res;
    }
};

/*
找到一塊最大的正方形可以fit 重疊區域
*/
