/*
2359. Find Closest Node to Given Two Nodes
*/

// 較簡潔寫法TC:O(n) SC:O(n)
class Solution {
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        vector<int> dist1 = getDist(edges,node1); // node1 到各點距離
        vector<int> dist2 = getDist(edges,node2);  // node2 到各點距離

        int minVal = INT_MAX;
        int maxVal = INT_MIN;
        int res = -1;
        for(int i = 0; i < n; i++){
            if(dist1[i] != -1 && dist2[i] != -1){
                maxVal = max(dist1[i], dist2[i]);
                if(maxVal < minVal){
                    minVal = maxVal;
                    res = i;
                }
                else if(maxVal == minVal){
                    res = min(res, i);
                }
            }
        }

        
        return res;

        
    }
    vector<int> getDist(vector<int>& edges, int node){
        vector<int> dist(edges.size(), -1);
        dist[node] = 0;
        int i = node;
        while(edges[i] != -1 && dist[edges[i]] == -1){
            int j = edges[i];
            dist[j] = dist[i] + 1;
            i = j;
        }

        return dist;
    }
};

// TC:O(n) SC:O(n)
class Solution {
    vector<int> dist1;
    vector<int> dist2;
    vector<bool> visited;
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        dist1 = vector<int>(n,-1); // node1 到各點距離
        dist2 = vector<int>(n,-1); // node2 到各點距離
        visited.resize(n);

        //計算node1 node2到各點距離
        DFS1(edges, node1, 0);
        DFS2(edges, node2, 0);

        int minVal = INT_MAX;
        int maxVal = INT_MIN;
        int res = -1;
        for(int i = 0; i < n; i++){
            if(dist1[i] != -1 && dist2[i] != -1){
                maxVal = max(dist1[i], dist2[i]);
                if(maxVal < minVal){
                    minVal = maxVal;
                    res = i;
                }
                else if(maxVal == minVal){
                    res = min(res, i);
                }
            }
        }

        
        return res;

        
    }
    void DFS1(vector<int>& edges, int node, int sum){
        if(node == -1) return;
        if(visited[node]) return;

        visited[node] = 1;
        dist1[node] = sum;
        DFS1(edges, edges[node], sum+1);
        visited[node] = 0;
    }
    void DFS2(vector<int>& edges, int node, int sum){
        if(node == -1) return;
        if(visited[node]) return;

        visited[node] = 1;
        dist2[node] = sum;
        DFS2(edges, edges[node], sum+1);
        visited[node] = 0;
    }
};

/*
此題為有向圖 並且每個點出度最多1 可以是0
要你求兩個點到某個點的距離之中取最大 其中最大的最小值中 是走到哪個節點 如果有很多節點可以得到相同數值 取節點較小的那個
此題應該是難在題目敘述比較難懂 其實就是遍歷兩次 去找node1與node2跟各個點的距離
最後再逐個遍歷一次去看兩個點都能到達的點誰最符合條件
*/
