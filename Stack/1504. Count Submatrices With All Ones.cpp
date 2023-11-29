/*
1504. Count Submatrices With All Ones
*/

// TC:O(2*m*n) SC:O(n)
class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m = mat.size(); int n = mat[0].size();
        vector<int> h(n+1,0);
        int res = 0;
        for(int i =0; i<m; i++){
            //一層一層往下算矩形可能性
            for(int j=0; j<n; j++){
                h[j+1] = (mat[i][j] == 0 ? 0:h[j+1]+1);
            }
            stack<int> stack;
            stack.push(0);
            int c = 0;
            for(int j = 1; j<=n; j++){
                while(!stack.empty() && h[stack.top()] > h[j]){
                    int p1 = stack.top();
                    stack.pop();
                    int p2 = stack.top();
                    c -= (h[p1]-h[j])*(p1-p2);
                } 
                c+=h[j];
                res+=c;
                stack.push(j);
            }
        }

        return res;
    }
};


/*
此題跟2866有點像 
會希望是單調遞增 如果不是的話要開始刪除前面多於可能會被計算的矩形
c[j] = c[j-1]+j[j] 會有這麼神奇的公式 如果用單調棧來想的話
c[j-1]等同於維護一個往後看都會比後面低的那些矩形的數量
*/
