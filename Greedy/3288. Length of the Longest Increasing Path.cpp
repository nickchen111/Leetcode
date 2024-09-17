/*
3288. Length of the Longest Increasing Path
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int maxPathLength(vector<vector<int>>& coordinates, int k) {
        int n = coordinates.size();
        int kx = coordinates[k][0], ky = coordinates[k][1];

        auto cmp = [](const vector<int>& a, const vector<int>& b){
            if(a[0] != b[0]) return a[0] < b[0];
            else return a[1] > b[1];
        };
        
        sort(coordinates.begin(), coordinates.end(),cmp);
        vector<int> q;
        
        for(int i = 0; i < n; i++){
            int x = coordinates[i][0], y = coordinates[i][1];
            if((x > kx && y > ky) || (x < kx && y < ky)){
                if(q.empty() || q.back() < y){
                    q.push_back(y);
                }
                else {
                    auto iter = lower_bound(q.begin(), q.end(), y);
                    *iter = y;
                }
            }
        }

        return q.size() + 1;
    }
};
