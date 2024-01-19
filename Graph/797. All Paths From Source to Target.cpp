/*
797. All Paths From Source to Target
*/

// TC: O(2^n) SC: O(n)
class Solution {
public:
    vector<int> onpath;
    vector<vector<int>> ans;
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        traverse(graph, 0);

        return ans;
    }
    void traverse(vector<vector<int>>& graph, int node){
        
        onpath.push_back(node);
        if(node == graph.size()-1) ans.push_back(onpath);


        for(const auto& neighbor : graph[node]){
            traverse(graph, neighbor);
        }

        onpath.pop_back();
        return;
    }
};

/*
解題思路
此題為dag 沒有環 要求從 0 到終點的走法為何？ 
圖即為多叉樹的題型概念 所以用遍歷的方式即可判斷
1.因為此題無環 也不需要用visited來判斷 只需用onpath記錄路徑 
2.最後當抵達時確認一下數值相等 再將路徑加入答案中即可


tc: o(2^n) sc: o(n)
時間複雜度：
在最壞情況下，當所有節點都直接連接到目標節點時，我們可能會遍歷所有的路徑。因此，時間複雜度是 O(2^n)，
其中 n 是節點的總數。每個節點最多可能被訪問兩次：一次是加入 onpath 向量，另一次是從 onpath 向量中移除。

空間複雜度：
這段程式碼使用了兩個二維向量，onpath 和 ans，以及遞迴呼叫時的函數調用堆疊空間。在遞迴的最壞情況下，onpath 向量的大小可能達到 n，
ans 向量的大小可能達到 2^n（每個節點最多可能有兩個父節點）。遞迴的最大深度也是 n，所以空間複雜度是 O(n)。
*/
