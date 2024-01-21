/*
3015. Count the Number of Houses at a Certain Distance I
*/

// TC:O(n^2) SC:O(n)
class Solution {
public:
    vector<int> countOfPairs(int n, int x, int y) {
        vector<vector<int>> graph(n+1);
        for(int i = 1; i < n; i++){
            graph[i].push_back(i+1);
            graph[i+1].push_back(i);
        }
        if(x != y) {
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        
        vector<int> res(n);
        
        for(int i = 1; i <= n; i++){
            queue<pair<int,int>> q; // node, step;
            q.push({i,0});
            vector<bool> visited(n+1);
            while(!q.empty()){
                int sz = q.size();
                while(sz--){
                    int cur = q.front().first;
                    int step = q.front().second;
                    q.pop();
                    visited[cur] = 1;
                    for(auto x : graph[cur]){
                        if(visited[x]) continue;
                        visited[x] = 1;
                        res[step] += 1;
                        q.push({x, step+1});
                    }
                }
            }
        }
      
        
        return res;
    }
};

/*
房子與房子之間數字相鄰的相連 然後還會有一條x y的相連xy還可以相同
問說從x到y每一步最短路徑的走法有幾種(自己不用走自己)
嘗試每一點都走過每個點 走過就不用走
*/
