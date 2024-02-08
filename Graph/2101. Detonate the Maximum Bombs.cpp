/*
2101. Detonate the Maximum Bombs
*/

// TC:O(n^2) SC:O(n)
class Solution {
    using LL = long long;
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int m = bombs.size();
        
        vector<vector<int>> graph(m);

        for(int i = 0; i < m; i++){
            LL x1 = bombs[i][0], y1 = bombs[i][1], r1 = bombs[i][2];
            for(int j = 0; j < m; j++){
                if(i == j) continue;
                LL x2 = bombs[j][0], y2 = bombs[j][1];
                if((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) <= r1*r1){
                    graph[i].push_back(j);
                }
            }
        }

        
        int res = 0;
        for(int i = 0; i < m; i++){
            queue<int> q;
            q.push(i);
            vector<bool> visited(m);
            int count = 0;
            while(!q.empty()){
                int sz = q.size();
                while(sz--){
                    int cur = q.front();
                    q.pop();
                    if(visited[cur]) continue;
                    visited[cur] = 1;
                    count += 1;
                    for(auto next : graph[cur]){
                        if(visited[next]) continue;
                        q.push(next);
                    }
                }
            }
            res = max(res, count);
        }

        
        return res;

    }
};

/*
2D的BFS選一個炸彈 如果此炸彈爆炸可以連帶影響他範圍內的炸彈爆炸 問最可以讓多少炸彈爆炸
一維的做法是sort by ending point然後去看自己的範圍內最多會有多少個
這題因為每個炸彈爆炸範圍都不同而且是個圓 很難用sort方式貪心 所以直接每個點都去檢查所有其餘所有點n^2來做
用公式去判斷 (xi-xy)^2 + (yi-yj)^2 <= ri^2
*/
