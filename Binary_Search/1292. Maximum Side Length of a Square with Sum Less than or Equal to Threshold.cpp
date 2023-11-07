/*
1292. Maximum Side Length of a Square with Sum Less than or Equal to Threshold
*/

//TC:O(n^2*lgn) SC:O(m*n)
class Solution {
    int m,n;
    vector<vector<int>> presum;
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        m = mat.size(); n = mat[0].size();
        presum = vector<vector<int>>(m+1,vector<int>(n+1,0));
        
        for(int i = 1; i<=m; i++){
            for(int j = 1; j<=n; j++){
                presum[i][j] = presum[i-1][j]+ presum[i][j-1]-presum[i-1][j-1]+mat[i-1][j-1];
            }
        }

        //邊長越大越不容易滿足 越小越容易滿足 binary search TC:O(n^2)搜索所有點 * O(1)算面積 * O(lgN)選邊長
        int left = 0; int right = min(m,n);
        while(left < right){
            int mid = left+(right-left+1)/2;
            if(OK(mid,threshold)){
                left = mid;
            }
            else right = mid-1;
        }

        return left;
    }

    bool OK(int len, int threshold){
        for(int i = len; i<=m; i++){
            for(int j = len; j<=n; j++){
                int sum = presum[i][j]-presum[i][j-len]-presum[i-len][j]+presum[i-len][j-len];
                if(sum <= threshold) return true;
            }
        }
        return false;
    }
};

/*
Brute force是n^4 求每個點的最大正方形會是n^2 遍歷所有點n^2 
如果邊長可以不再n^2時間找到的話會大大提升時間效率 所以想到用猜的lgＮ的時間去猜一個邊長 
至於面積的話想到用O(1)的presum處理
*/
