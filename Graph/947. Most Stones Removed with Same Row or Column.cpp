/*
947. Most Stones Removed with Same Row or Column
*/

// TC:O(n) SC:O(n)
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
            parent[y] = x;
        }
        else parent[x] = y;
    }
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        parent.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }

        unordered_map<int, vector<int>> row;
        unordered_map<int, vector<int>> col; 
        for(int i = 0; i < stones.size(); i++){
            int x = stones[i][0], y =  stones[i][1];
            row[x].push_back(i);
            col[y].push_back(i);
        }

        for(auto &[x, r] : row){
            int m = r.size();
            for(int i = 1; i < m; i++){
                union_(r[0], r[i]);
            }
        }

        for(auto &[y, c] : col){
            int m = c.size();
            for(int i = 1; i < m; i++){
                union_(c[0], c[i]);
            }
        }

        unordered_set<int> set;
        for(int i = 0; i < n; i++){
            int cur = find(i);
            if(set.find(cur) == set.end()){
                set.insert(cur);
            }
        }

        return n - (int) set.size();

    }
};


/*
x x
x x
把跟其他石頭連結的越少的石頭如果有機會的話就優先去掉 貪心的做法
有dp嗎?
按照x軸排序 一樣就排序y 但是y軸可能差很多 難想dp 看起來狀態轉移不是那麼可行
UF 每顆石頭都去做DFS!? 被看過的就畫記號不用看了 所以連結方式會是按照x 與 y軸相同的去做連結  
unordered_map<int, vector<pair<int,int>>> row;
unordered_map<int, vector<pair<int,int>>> col; 
*/
