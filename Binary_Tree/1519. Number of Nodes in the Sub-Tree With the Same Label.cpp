/*
1519. Number of Nodes in the Sub-Tree With the Same Label
*/

// TC:O(n*26) SC:O(n+26)
class Solution {
    vector<int> res;
public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int>> graph(n);
        res.resize(n);
        for(auto edge : edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        int count[26] = {};
        DFS(0, graph, labels, count);
        
        return res;
    }
    void DFS(int cur, vector<vector<int>>& graph, string& labels, int count[]){
        if(res[cur] == 0){
            res[cur] = 1;  
            for(auto neighbor : graph[cur]){
                int count2[26] = {};
                DFS(neighbor, graph, labels, count2);
                for(int i = 0; i < 26; i++){
                    count[i] += count2[i];
                }
            }
            count[labels[cur]-'a'] += 1;
            res[cur] = count[labels[cur]-'a'];
        }
    }
};

/*
樹上的節點資訊有自己本身0-n-1的數字以及他的label a-z 
問說自己的子數中包含自己有多少個label跟自己一樣的字母
n = 10 ^ 5
我想到的是某個節點所擁有的資訊都是從他的子樹加上他自己來的
TC:O(n*26) SC:O(n+26)
*/
