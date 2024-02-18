/*
3044. Most Frequent Prime
*/


// DFS + 埃氏篩   m = 6, n = 6, k = 7, n = maxVal we can merge in array, t = number of prime we collect TC:O(m*n*k*m + nlglgn) SC:O(t + n)
class Solution {
    int m, n;
    vector<int> Eratosthenes(int t){
        vector<int> q(t+1,0);
        for(int i = 2; i<=sqrt(t); i++){
            if(q[i] == 1) continue;
            int j = 2*i; 
            while(j<=t){
                q[j] = 1;
                j+=i;
            }
        }
        
        return q;
    }
    vector<int> check;
    unordered_map<int,int> map;
public:
    int mostFrequentPrime(vector<vector<int>>& mat) {
        m = mat.size();
        n = mat[0].size();
        int maxV = max(m,n);
        check = Eratosthenes(pow(10,maxV) + 1);
        // 上面 下面 右 左 左上 右下 左下 右上
        vector<vector<int>> dirs = {{0,1},{0,-1},{1,0},{-1,0},{-1,-1},{1,1},{1,-1},{-1,1}};
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int cur = mat[i][j];
                for(int k = 0; k < dirs.size(); k++){
                   DFS(mat, cur, i+dirs[k][0], j + dirs[k][1], k);   
                }
            }
        }
        // 6 * 6 * 8 * 6
        
        
        
        int res = -1;
        int maxFreq = 0;
        if(map.size() > 0){
            for(auto p : map){
                if(maxFreq < p.second){
                    maxFreq = p.second;
                    res = p.first;
                }
                else if(maxFreq == p.second){
                    res = max(res, p.first);
                }
            }
        }
        
        return res;
    }
    
    void DFS(vector<vector<int>>& mat, int cur, int x, int y, int k){
        if(x >= m || y >= n || x < 0 || y < 0) return;
        cur = cur*10 + mat[x][y];
        if(check[cur] == 0) map[cur] += 1;
        
        if(k == 0){
            DFS(mat,cur,x,y+1, k);
        }
        if(k == 1){
            DFS(mat, cur, x,y-1,k);
        }
        if(k == 2){
            DFS(mat, cur, x+1,y,k);
        }
        if(k == 3){
            DFS(mat, cur, x-1,y,k);
        }
        if(k == 4){
            DFS(mat, cur, x-1,y-1,k);
        }
        if(k == 5){
            DFS(mat, cur, x+1,y+1,k);
        }
        if(k == 6){
            DFS(mat, cur, x+1,y-1,k);
        }
        if(k == 7){
            DFS(mat, cur, x-1,y+1,k);
        }

    }
};



/*
此題給你一個m*n格子 問說你在每個點皆可以往八個方向前進 每個格子裡面會有1~9的數字 問你出現頻率最高的質數是多少 如果頻率相同選較大的質數
很明顯是用DFS每個點遍歷八個方向 並且一旦確定方向就不能改變 再來就是用埃氏篩快速判斷當前累加的點是否為質數 在用一個hash map紀錄此質數出現的次數 最後比較頻率大小即可
*/
