/*
1042. Flower Planting With No Adjacent
*/

// TC:O(n) SC:O(n)
class Solution {
    vector<int> res;
public:
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {
        int m = paths.size();
        vector<vector<int>> graph(n);
        for(auto path : paths){
            graph[path[0]-1].push_back(path[1]-1);
            graph[path[1]-1].push_back(path[0]-1);
        }

       
        res.resize(n);
        for(int i = 0; i < n; i++){
            traverse(i,graph);
        }

        return res;
    }
    void traverse(int node, vector<vector<int>>& graph){
        
        
        int color[5] = {};
        //  將此節點以外的連接點都先確認是否用過
        for(auto x : graph[node]){
            if(res[x] != 0){
                color[res[x]] = 1;
            }
        }
        
        for(int i = 1; i < 5; i++){
            if(color[i] == 0){
                res[node] = i;
            }
        }
        

    }
};

/*
此題跟bipartite很像 但改換成四種顏色讓你塗鴉
返回他可以塗鴉成功的塗法
因為這題規定最多就是三條路徑 代表每個節點都嘗試一遍找可以的顏色應該是沒問題
如果規定沒有加上最多三條路線 並且又說一定有答案 那麼就是NP問題要用回溯來試試
*/
