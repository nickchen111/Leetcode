# graph

圖本質上就是個高級點的多叉树，適用於树的 DFS/BFS 遍歷算法，全部適用於圖。
用adjacent list和adjacent matrix的存储方式 通常鄰接表用的比較頻繁

我们再明确一个图论中特有的度（degree）的概念，在无向图中，「度」就是每个节点相连的边的条数。
由于有向图的边有方向，所以有向图中每个节点「度」被细分为入度（indegree）和出度（outdegree）

如果图包含环，遍历框架就要一个 visited 数组进行辅助 還有搭配onpath(很像track)
这个 onPath 数组的操作很像前文 回溯算法核心套路 中做「做选择」和「撤销选择」，区别在于位置：回溯算法的「做选择」和「撤销选择」在 for 循环里面，
而对 onPath 数组的操作在 for 循环外面。(因為回溯在意edge graph在意node)

// 记录被遍历过的节点
vector<bool> visited;
// 记录从起点到当前节点的路径
vector<bool> onPath;

/* 图遍历框架 */
void traverse(Graph graph, int s) {
    if (visited[s]) return;
    // 经过节点 s，标记为已遍历
    visited[s] = true;
    // 做选择：标记节点 s 在路径上
    onPath[s] = true;
    for (int neighbor : graph.neighbors(s)) {
        traverse(graph, neighbor);
    }
    // 撤销选择：节点 s 离开路径
    onPath[s] = false;
}

Graph限制邊界的條題目：
對於此種網格類的題目 然後他又給你這種和邊界上的節點有關係 都可以換種角度思考 例如可從邊界出發
