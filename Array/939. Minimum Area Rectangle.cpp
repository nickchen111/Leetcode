/*
939. Minimum Area Rectangle
*/

// TC:O(n*2*) SC:O(n*2)
class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        //將每個點放入以確保是否存在這些點
        unordered_map<int, unordered_set<int>> map;
        for(auto point : points){
            map[point[0]].insert(point[1]);
        }

        // x盡量小 y 盡量大 才可以從左上包括到右下找點
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            if(a[1] != b[1]){
                return a[1] > b[1];
            }
            else return a[0] < b[0];
        };
        sort(points.begin(), points.end(), cmp);

        int res = INT_MAX;
        for(int i = 0; i < points.size(); i++){
            for(int j = i+1; j < points.size(); j++){
                int x1 = points[i][0];
                int y1 = points[j][1];
                int x2 = points[j][0];
                int y2 = points[i][1];
                if(x1-x2 == 0 || y1 - y2 == 0) continue;
                if(map[x1].find(y1) != map[x1].end() && map[x2].find(y2) != map[x2].end()){
                    int area = abs(points[i][0]-points[j][0])*abs(points[i][1]-points[j][1]);
                    res = min(res, area);
                }
            }
        }

        return res == INT_MAX ? 0:res;

        
    }
};

/*
給一堆點 問說他能組成的最小矩形 如果沒辦法組成return 0
兩個點就可以組成矩形
A  C
D. B
for(A){
    for(B){
        C D in set
        area = ?
        res = min(res, area);
    }
}
如何定義set
1. set<pair<int,int>> set; 每次要查找的數量眾多
2. 可以只根據X軸設立unordered_set 每次查找就不用那麼花時間
此題Sort後 效率會比較大
*/
