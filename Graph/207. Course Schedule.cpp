/*
207. Course Schedule
*/

//DFS TC: O(V+E) SC:O(V+E)
class Solution {
public:
    vector<bool> onpath; //蛇身
    vector<bool> visited;//走過的路徑
    bool hascycle = false;
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        //建立鄰接表
        vector<vector<int>> graph(numsCourses); 
        for(auto edge: prerequisites){
            int from = edge[1];
            int to = edge[0];
            graph[from].push_back(to); //被依賴的關係
        }
        
        onpath = vector<bool>(numCourses, false);//初始化
        visited = vector<bool>(numCourses, false);//走過的路徑      
        for(int i=0; i<numCourses; i++){
            traverse(graph, i);
        }
        return !hascycle;

    }

    void traverse(vector<vector<int>>& graph, int s){ //環的判斷
        if(onpath[s] == true) hascycle = true;
        if(visited[s] || hascycle) return;

        visited[s] = true;
        onpath[s] = true;
        for(auto x:graph[s]){
            traverse(graph, x);
        }
        onpath[s] = false;//這裡就很像回溯法了 但是他的撤銷選擇是放在外面的 因為graph在意的是node 而回溯法在意的是edge
    }
};


/*
解題思路：
此題是一個  dag考題
那牽扯到dag就可以感覺到是graph
是graph的話 就可以用遍歷的方式 
dag 的話 遍歷方式加上 visited 跟 onpath
此題只求他是否可以修完這門課 亦即是否回有deadlock 
如此一來只需要在乎是否會形成一個cycle
可以用dfs or bfs來偵測有無  cycle

1.先將題目中的敘述放進創建的graph容器中
2.開始遍歷此graph
3.dfs遍歷的話就會想到 a. 路徑 b. 選擇 ｃ.結束條件
4.判斷是否為一cycle 

graph的dag重要特點： 可以把visited想成蛇走過的路徑 onpath為蛇身 如果成環的話代表蛇咬到自己了
*/

//BFS TC:O(V+E) SC:O(V+E)
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        //建立鄰接表以及各門課的入度
        auto graph = vector<vector<int>>(numCourses);
        vector<int> indegree(numCourses);

        for(auto edge:prerequisites){
            graph[edge[1]].push_back(edge[0]);
            indegree[edge[0]]++;
        }

        //將入度0的加入隊列
        queue<int> q;
        for(int i = 0; i<numCourses; i++){
            if(indegree[i] == 0) q.push(i);
        }

        //開始計算count 數量是否等於課程數量
        int count = 0;
        while(!q.empty()){
            int num = q.front();
            q.pop();
            count++;
            for(auto neighbor:graph[num]){
                indegree[neighbor]--;
                if(indegree[neighbor] == 0) q.push(neighbor);
            }
        }

        return count == numCourses;

    }
};

/*
解題思路：
此題是一個dag考題 所以需要去判斷有沒有環
1.建立一graph
2.用bfs遍歷有沒有環 方法為不斷找出indegree =0的點加入queue 然後判斷count數量是否等於numcourses

需要做的事： graph count queue ....
*/


// labu大的bfs
class Solution{
public:
// 主函数
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    // 建图，有向边代表「被依赖」关系
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);
    for(auto edge:prerequisites){//建立graph
        int from = edge[1];
        int to = edge[0];
        graph[from].push_back(to);
        indegree[to]++;//計算每個點目前的indegree
    }
//前面做了點改動

    // 根据入度初始化队列中的节点
    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) {
            // 节点 i 没有入度，即没有依赖的节点
            // 可以作为拓扑排序的起点，加入队列
            q.push(i);

        }
    }

    // 记录遍历的节点个数
    int count = 0;
    // 开始执行 BFS 循环
    while (!q.empty()) {
        // 弹出节点 cur，并将它指向的节点的入度减一
        int cur = q.front();
        q.pop();
        count++;
        for (int next : graph[cur]) {

            indegree[next]--;
            if (indegree[next] == 0) {
                // 如果入度变为 0，说明 next 依赖的节点都已被遍历
                q.push(next);
            }
        }
    }

    // 如果所有节点都被遍历过，说明不成环
    return count == numCourses;
}
};
