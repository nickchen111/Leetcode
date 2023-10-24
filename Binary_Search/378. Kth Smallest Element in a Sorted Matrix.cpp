/*
378. Kth Smallest Element in a Sorted Matrix
*/

class Solution {
    int m,n;
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        //先用二分找去猜某個數字 此數字比他小包含他自己的數目是否等於題目要求
        //判斷數目的函式就是用240題的寫法加上一點點的修改
        m = matrix.size(); n = matrix[0].size();

        long lower = INT_MIN;
        long upper = matrix[m-1][n-1];

        while(lower < upper){
            long mid = lower + (upper - lower)/2;
            if(count(mid,matrix) >= k){
                upper = mid;
            }
            else if(count(mid,matrix) < k){
                lower = mid+1;
            }
        }

        return lower;
    }
    long count(int mid, vector<vector<int>>& matrix){
        int i = m-1;
        int j = 0;
        long res = 0;
        while(i >= 0 && j < n){
            if(matrix[i][j] > mid){
                i--;
            }
            else if(matrix[i][j] <= mid){
                res +=(i+1);
                j++;
            }
        }
        return res;
    }
};

// PQ+BFS TC:O((m+n)*lgm) SC:O(m)
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        //優先隊列做法 一樣是要善用此題從小到大陣列性質
        int m = matrix.size();
        int n = matrix[0].size();
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        //先將第一列的元素push進去 第一列相當於每一行中最小的選手們
        for(int i = 0; i < m; i++){
            pq.push({matrix[i][0],i,0});
        }

        int res;
        while(!pq.empty() && k>0){
            res = pq.top()[0];
            int i = pq.top()[1];
            int j = pq.top()[2];
            pq.pop();
            if(j+1 < n){
                pq.push({matrix[i][j+1],i,j+1});
            }
            k--;
        }

        return res;
    }
};

/*
此題為240題的follow up 
有兩種解法
1. Binary search
2. PQ
*/
