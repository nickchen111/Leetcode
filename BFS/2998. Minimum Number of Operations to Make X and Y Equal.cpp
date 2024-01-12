/*
2998. Minimum Number of Operations to Make X and Y Equal
*/

// TC:O(4*n) SC:O(n)
class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
        if(x <= y) return y-x;
        
        queue<pair<int,int>> q;
        q.push({x,0}); // x, 目前操作數
        vector<int> visited(20000,0);
        while(!q.empty()){
            auto[x, sp] = q.front();
            q.pop();
            if(x == y) return sp;
            
            if(x % 11 == 0 && !visited[x/11]){
                q.push({x/11,sp+1});
                visited[x/11] = 1;
            }
            if(x % 5 == 0 && !visited[x/5]){
                q.push({x/5,sp+1});
                visited[x/5] = 1;
            }
            if(x+1 < 20000 && !visited[x+1]){
                q.push({x+1,sp+1});
                visited[x+1] = 1;
            }
            if(x-1 > 0 && !visited[x-1]){
                q.push({x-1,sp+1});
                visited[x-1] = 1;
            }
        }
        
        return -1;
    }
};

/*
問說要讓x 變成y 每次可以做四種操作任一種 1, +1 2. -1 3. 如果整除5 除5 4. 如果整除11 除11問說最少操作幾次可以變成y
此題週賽沒做出來 但是有考慮到一些corner case ex: 加法只會變大 剩下的都是會變小 除五除十一都會有兩種方式 
但是沒考慮到要往BFS方向去想 題目是問最少的操作次數 這是一個hint 並且每次也都只會有四種選擇 每次的選擇也都只是讓操作次數加一
*/
