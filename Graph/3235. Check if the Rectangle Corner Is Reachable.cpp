/*
3235. Check if the Rectangle Corner Is Reachable
*/

// TC:O(n^2 * lgn) SC:O(n)
class Solution {
    vector<int> parent;
    int find(int x){
        if(x != parent[x]){
            parent[x] = find(parent[x]);
        }
        
        return parent[x];
    }
    void union_(int x, int y){
        x = find(x);
        y = find(y);
        if(x < y){
            parent[x] = y;
        }
        else parent[y] = x;
    }
public:
    bool canReachCorner(int X, int Y, vector<vector<int>>& circles) {
        int n = circles.size();
        parent.resize(n+2); // n 指定為上跟左邊界的parent n+1 為右跟下
        iota(parent.begin(), parent.end(), 0);
        
        
        for(int i = 0; i < n; i++){
            int x = circles[i][0], y = circles[i][1], r = circles[i][2];
            if(x-r <= 0 || y+r >= Y) union_(i, n);
            if(x+r >= X || y-r <= 0) union_(i,n+1);
            for(int j = i + 1; j < n; j++){
                int nx = circles[j][0], ny = circles[j][1], nr = circles[j][2];
                if((long long)(x-nx)*(x-nx) + (long long)(y-ny)*(y-ny) <= (long long)(r+nr)*(r+nr)){
                    union_(i,j);
                }
            }
            
            if(find(n) == find(n+1)) return false;
        }
        
        return true;
        
    }
};

/*
"這題的突破口是要先看出 如果左或者上邊界 跟 右或者下邊界有聯通 那就肯定是無法抵達終點，並且這題出的時候少了個條件，園心肯定要在矩形內 否則超難
再來是要想到因為要連接 所以會有聯通感， 我原本是想到用類似sweeping line的方式 先sort 再慢慢連起來，但是這樣做很難界定下一個圓的範圍要用哪個當作判斷標準
因為要判斷兩個圓是否有相交的話要用距離公式 (x-nx)*(x-nx) + (y-ny)*(y-ny) <= (r+nr)*(r+nr)
所以這時候會想到用聯通量概念來快速連接兩點，每次回圈都以某一個圓當出發點去traverse所有其他的圓"
*/
