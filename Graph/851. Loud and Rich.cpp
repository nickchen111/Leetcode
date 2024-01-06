/*
851. Loud and Rich
*/

// DFS O(n) SC:O(n)
class Solution {
    unordered_map<int, vector<int>> richer2; // poor -> rich
    vector<int> res;
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        for(auto rich : richer) richer2[rich[1]].push_back(rich[0]);

        res = vector<int> (quiet.size(),-1);

        for(int i = 0; i < quiet.size(); i++) DFS(i,quiet);

        return res;
    }

    int DFS(int i, vector<int>& quiet){
        if(res[i] >= 0) return res[i];
        res[i] = i;
        for(int j : richer2[i]){
            if(quiet[res[i]] > quiet[DFS(j, quiet)]) res[i] = res[j];
        }

        return res[i];
    }
};


// BFS TC:O(n^2) SC:O(n)
class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        vector<vector<int>> graph(n);
        for(auto rich : richer){
            graph[rich[1]].push_back(rich[0]); // rich[0]比rich[1]有錢
        }
        
        vector<int> res(n);
        for(int i = 0; i < n; i++){
            int minVal = quiet[i];
            int person = -1;
            queue<int> q;
            q.push(i);
            vector<int> visited(n);

            while(!q.empty()){
                int cur = q.front();
                q.pop();
                if(visited[cur]) continue;
                visited[cur] = 1;
                for(auto neighbor : graph[cur]){
                    if(visited[neighbor]) continue;
                    if(quiet[neighbor] < minVal){
                        person = neighbor;
                        minVal = quiet[neighbor];
                    }
                    q.push(neighbor);
                }
            }
            res[i] = (person == -1 ? i : person);
        }

        return res;
    }
};

/*
每個人確保了他們的安靜值 已經有錢程度比較
他要問說隨便給你一個人 請找出比他有錢的人之中 最安靜的那位 quiet數值最小
用n^2的解法 先做出graph 哪些人比我有錢 逐個遍歷再從他們之中挑出最安靜的那位 
可以用DFS 只要去剪枝 如果這個人遍歷過 那麼直接返回他的值即可並且比當前的值更加安靜
*/
