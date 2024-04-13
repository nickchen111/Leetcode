/*
3111. Minimum Rectangles to Cover Points
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    int minRectanglesToCoverPoints(vector<vector<int>>& points, int w) {
        auto cmp = [](const vector<int> & a, const vector<int> & b){
            if(a[0] != b[0]) return a[0] < b[0];
            else return a[1] < b[1];
        };
        sort(points.begin(), points.end(), cmp);
        
        int count = 0;
        int n = points.size();
        int j = 0;
        for(int i = 0; i < n; i++){
            while(j < n && points[i][0] + w >= points[j][0]){
                j++;
            }
            count += 1;
            i = j-1;
        }
        
        return count;
    }
};

/*
用rect把點都涵蓋起來 但是rect x軸距離不能超過w 問說最少需要幾個rect
且rect必須從(x1,0) 出發
*/
