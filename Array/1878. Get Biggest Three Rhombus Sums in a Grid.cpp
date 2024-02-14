/*
1878. Get Biggest Three Rhombus Sums in a Grid
*/

//  Presum TC:O(m*n*m) SC:O(m*n)
class Solution {
    int presum1[100][100]; // "\"
    int presum2[100][100]; // "/"
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                presum1[i][j] = (i-1 >= 0 && j-1 >= 0 ? presum1[i-1][j-1] : 0) + grid[i][j];
            }
        }
        for(int i = 0; i < m; i++){
            for(int j = n-1; j >= 0; j--){
                presum2[i][j] = (i-1 >= 0 && j+1 < n ? presum2[i-1][j+1] : 0) + grid[i][j];
            }
        }

        priority_queue<int, vector<int>, less<int>> pq; //只需要三個   
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int R = min(i,j);
                R = min(R, min(m-i-1,n-j-1));
                pq.push(grid[i][j]);
                for(int r = 1; r <= R; r++){
                    int sum = 0;
                    int x1,y1,x2,y2;
                    x1 = i - r; y1 = j; // 上面
                    x2 = i; y2 = j + r; //右邊
                    sum += presum1[x2][y2] - ((x1-1 >= 0 && y1-1 >= 0) ? presum1[x1-1][y1-1] : 0);

                    x1 = i; y1 = j-r; // 左邊
                    x2 = i+r; y2 = j; //下面
                    sum += presum1[x2][y2] - ((x1-1 >= 0 && y1-1 >= 0) ? presum1[x1-1][y1-1] : 0);
                   
                    x1 = i-r; y1 = j;
                    x2 = i; y2 = j-r;
                    sum += presum2[x2-1][y2+1] - presum2[x1][y1];

                    x1 = i; y1 = j + r;
                    x2 = i+r; y2 = j;
                    sum += presum2[x2-1][y2+1] - presum2[x1][y1];
                    pq.push(sum);
                }
            }
        }

        vector<int> res;
        while(!pq.empty()){
            if(res.empty() || (res.size() < 3 && res.back() != pq.top())) 
                res.push_back(pq.top());
            pq.pop();
            if(res.size() == 3) break;
        }

        return res;
    }
};

//Brute force TC:O(m*n*m*n) SC:O(n)
class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        priority_queue<int, vector<int>, less<int>> pq; //只需要三個   
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                int maxLen = min(i,j);
                maxLen = min(maxLen, min(m-i-1,n-j-1));
                vector<int> temp = helper(grid,i,j,maxLen);
                for(int t = 0; t < temp.size(); t++){
                    pq.push(temp[t]);
                }
            }
        }

        vector<int> res;
        while(!pq.empty()){
            if(res.empty() || (res.size() < 3 && res.back() != pq.top())) 
                res.push_back(pq.top());
            pq.pop();
            if(res.size() == 3) break;
        }

      

        return res;
    }

    vector<int> helper(vector<vector<int>>& grid, int x, int y, int maxLen){
        vector<int> res;
        for(int i = 0; i <= maxLen; i++){
            if(i == 0) res.push_back(grid[x][y]);
            else{
                 //遍歷四個方向
                
                //目標
                int leftx = x;
                int lefty = y - i;
                //上面的點
                int curx = x-i;
                int cury = y;
                int sum = grid[curx][cury];
                //往左下角
                while(curx != leftx && cury != lefty){
                    curx +=1;
                    cury -= 1;
                    sum += grid[curx][cury];
                }
                //往右下角
                int rightx = x;
                int righty = y+i;
                curx = x-i;
                cury = y;
                while(curx != rightx && cury != righty){
                    curx +=1;
                    cury += 1;
                    sum += grid[curx][cury];
                }
               
                int downx = x + i;
                int downy = y;
                
                while(leftx != downx && lefty != downy){
                    leftx +=1;
                    lefty += 1;
                    sum += grid[leftx][lefty];
                }
               
                while(rightx != downx && righty != downy){
                    rightx +=1;
                    righty -= 1;
                    sum += grid[rightx][righty];
                }
                
                sum -= grid[downx][downy];
                res.push_back(sum);
            }
        }
        return res;
    }
};


/*
找出一個矩形中最大的sum的三個菱形 sum是由組成他的點來構成的
代表不一定是越大sum越多
目前的想法是每一點都當作是中心那點看能否做出菱形 
n = 50, m = 50 50^4 暴力枚舉還算可以過
但如果想再優化就是用presum 去做左上到右下 右上到左下的presum 少一個維度的時間複雜度
*/
