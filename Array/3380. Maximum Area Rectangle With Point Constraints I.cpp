/*
3380. Maximum Area Rectangle With Point Constraints I
*/


// TC:O(n^4) SC:O(n)
class Solution {
public:
    int maxRectangleArea(vector<vector<int>>& points) {
        unordered_map<int, unordered_set<int>> map;
        for (const auto& point : points) {
            map[point[0]].insert(point[1]);
        }

        int maxArea = -1;
        int n = points.size();

        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                int x1 = points[i][0], y1 = points[i][1];
                int y2 = points[j][1], x2 = points[j][0];
                if(x1 != x2 && y1 != y2 && map[x1].find(y2) != map[x1].end() && map[x2].find(y1) != map[x2].end()) {
                    bool isValid = true;
                    int xmin = min(x1,x2), xmax = max(x1, x2), ymin = min(y1,y2), ymax = max(y1,y2);
                    for(auto &point : points) {
                        int x = point[0], y = point[1];
                        if((x >= xmin && x <= xmax && y > ymin && y < ymax) || (x > xmin && x < xmax && y >= ymin && y <= ymax)){
                            isValid = false;
                            break;
                        }
                    }
                    
                    if(isValid) {
                        maxArea = max(maxArea, abs(x1-x2) * abs(y1-y2));
                    }
                }
            }
        }

        return maxArea;
    }
};
