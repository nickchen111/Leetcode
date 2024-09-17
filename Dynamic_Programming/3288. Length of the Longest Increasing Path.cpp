/*
3288. Length of the Longest Increasing Path
*/

// TC:O(nlgn) SC:O(n)
// "LIS
// 二分 Binary Search"

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

/*
跟 LC354 俄羅斯娃娃很像，有個排序技巧x軸正常由小到大但是y要是由大到小 這樣可以避免 x軸相同的狀況 y軸不同會重複計算
並且這題還可以做follow up 如果要你算每個點都要單獨包含的n個情況 如果用原本做法就是n^2lgn 如果要變成nlgn 就是用前後綴分解 看透二分出來的答案性質 就可以知道走到某個點的時候他可以有的最長遞增子序列是多少
*/
