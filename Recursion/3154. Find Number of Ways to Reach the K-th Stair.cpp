/*
3154. Find Number of Ways to Reach the K-th Stair
*/

// TC:O(2^n) n = 31 包含memo剪枝 SC:O(pos*32*2)
class Solution {
    unordered_map<int, vector<vector<int>>> memo; // pos -> jump狀況 -> 使用的次數
    int res = 0;
public:
    int waysToReachStair(int k) {
        
        
        
        DFS(1, 0, 0, k);
        
        return res;
        
    }
    int DFS(int pos, int jump, bool rev, int k){
        if(jump > 30) return 0;
        if(memo.find(pos) != memo.end() && memo[pos][jump][rev] != -1) return memo[pos][jump][rev];
        int count = (pos == k);
        
        if(pos != 0 && rev == 0){
            count += DFS(pos-1, jump, 1, k);
        }
        if(pos + (1<<jump) <= k+1)
            count += DFS(pos+(1<<jump), jump+1, 0, k);
        
        memo[pos].resize(32, vector<int>(2,-1));
        memo[pos][jump][rev] = count;
        res = max(res, count);
        
        return count;
        
    }
};

/*
從1 開始跳
1. 往回走一格，但不能連續用or 在stair 0 上用
2. 走到i+ 2^j格, j = j + 1, initial j = 0;
問最後alice 有多少種方法走到k格上 2^30次方可以是10^9
1 + ? = 10^9 30跳的時候 肯定會爆炸超過 2^29 = 5e8, 2^30 = 1e9 up
只有當跳到比k大1以上的格子就是結束 -> BFS or DP+memo
BFS -> TLE
但目前問題是pos位置太大了1e9 所以不可能每個位置都存-> Hash Map 再來就是條件上的不同 jump狀況以及是否能往回走
原來resize 可以直接做二維
*/
