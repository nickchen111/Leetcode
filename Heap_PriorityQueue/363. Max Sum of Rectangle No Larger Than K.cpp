/*
363. Max Sum of Rectangle No Larger Than K
*/

// TC:O(m*m*n*n*lgn)  SC:O(n)
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        if(m ==0) return 0;
        int n = matrix[0].size();
        //此為當m比n大時 lgm會省更多時間
        if(m>n){
            vector<vector<int>>matrix2(n,vector<int>(m,0));
            for (int i=0; i<m; i++)
                for (int j=0; j<n; j++)
                    matrix2[j][i]=matrix[i][j];
            return maxSumSubmatrix(matrix2,k);
        }
        int res = INT_MIN;
        for(int i=0; i<m; i++){
            vector<int> temp(n,0);//只有在換上界的時候才需要更新
            for(int j=i; j<m; j++){
                for(int t = 0; t < n; t++){
                    temp[t]+=matrix[j][t];
                }
                res = max(res,helper(temp,k));
            }
        }

        return res;
    }
    int helper(vector<int>& temp, int k){
        int res = INT_MIN/2;
        int presum = 0;
        multiset<int> set({0});//只有一個[y] 這種情況也要被找到

        for(int i = 0; i<temp.size(); i++){
            presum+=temp[i];
            auto iter = set.lower_bound(presum-k);
            if(iter != set.end()){
                res = max(res,presum-*iter);
            }
            set.insert(presum);
        }

        return res;
    }
};
/*
此題兩個思想
1. 在大矩陣中找小矩陣 會想將他拍扁 變成一維判斷
O(m*m*n*n*lgn) M*M 確定上下邊界 每次都要run一下column n*n 在找的過程就是lgn
presum[j]-presum[i] <=k
presum[i] >= presum[j]-k;
2.常用到的presum快速找到某個區域和
*/
