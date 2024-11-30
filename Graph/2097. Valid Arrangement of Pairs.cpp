/*
2097. Valid Arrangement of Pairs
*/

// 1130 TC:O(n) SC:O(n)
class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        unordered_map<int, vector<int>> next;
        unordered_map<int, int> deg;
        vector<vector<int>> res;
        for(auto &pair : pairs) {
            next[pair[0]].push_back(pair[1]);
            deg[pair[0]] -= 1;
            deg[pair[1]] += 1;
        }
        auto dfs = [&](auto &&dfs, int cur) -> void {
            vector<int> &e = next[cur];
            while(!e.empty()) {
                int nxt = e.back();
                e.pop_back();
                dfs(dfs, nxt);
                res.push_back({cur,nxt});
            }
        };
        for(auto it = deg.begin(); it != deg.end(); it++) {
            if(it->second == -1) dfs(dfs, it->first);
        }
        if(res.empty()) dfs(dfs, deg.begin()->first);
        reverse(res.begin(), res.end());

        return res;
    }
};

// TC:O(E+V) SC:O(E+V)
class Solution {
    unordered_map<int,queue<int>> next;
    unordered_map<int,int> in;
    unordered_map<int,int> out;
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        //計算出度簡入度等於1的當作起點
        
        for(auto pair:pairs){
            next[pair[0]].push(pair[1]);
            in[pair[1]]+=1;
            out[pair[0]]+=1;
        }
        int start = pairs[0][0];// 如果沒有出度減入度為一 任意點都可以是起點
        for(auto x:next){
            int num = x.first;
            if(out[num]-in[num] == 1){
                start = num;
                break;
            }
        }
        vector<int> path;
        DFS(start,path);
        reverse(path.begin(),path.end());
        vector<vector<int>> res;
        for(int i=0; i<path.size()-1; i++){
            res.push_back({path[i],path[i+1]});
        }

        return res;
    }   

    void DFS(int start, vector<int>& path){
        while(next[start].size() > 0){
            int nxt = next[start].front();
            next[start].pop();
            DFS(nxt,path);
        }

        path.push_back(start);
    }
};
/*
此題跟332是類似題目 但這題比較難在要先確定從哪點出發 藉由歐拉路徑的規則出度減入度為一的點是起點 如果沒有這點那就選任一點都可是起點
另外要返回的資料結構會是edge形式 所以程式碼也有所不同
*/
