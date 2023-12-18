/*
1738. Find Kth Largest XOR Coordinate Value
*/

// Binary Search TC:O(m*n*32) SC:O(m*n)
class Solution {
    int presum[1001][1001];
    int m,n;
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        m = matrix.size();
        n = matrix[0].size();
        
        presum[0][0] = matrix[0][0];

        for(int i = 1; i < m; i++){
            presum[i][0] = presum[i-1][0] ^ matrix[i][0]; 
        }
        for(int j = 1; j < n; j++){
            presum[0][j] = presum[0][j-1] ^ matrix[0][j]; 
        }

        for(int i = 1; i < m; i++){
            for(int j = 1; j < n; j++){
                presum[i][j] = presum[i-1][j] ^ presum[i][j-1] ^ presum[i-1][j-1] ^ matrix[i][j];
            }
        }

        int left = 0; int right = INT_MAX/2;
        while(left < right){
            int mid = left + (right - left + 1)/2;
            if(count(mid) < k){
                right = mid - 1;
            }
            else left = mid;
        }

        return left;
    }

    int count(int mid){
        int res = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(presum[i][j] >= mid) res++;
            }
        }

        return res;
    }
};

// Heap TC:O(m*n*lgk) SC:O(m*n)
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> presum(m, vector<int>(n));
        presum[0][0] = matrix[0][0];

        priority_queue<int, vector<int>, greater<int>> pq;
        pq.push(presum[0][0]);
        for(int i = 1; i < m; i++){
            presum[i][0] = presum[i-1][0] ^ matrix[i][0]; 
            pq.push(presum[i][0]);
            if(pq.size() > k) pq.pop();
        }
        for(int j = 1; j < n; j++){
            presum[0][j] = presum[0][j-1] ^ matrix[0][j]; 
            pq.push(presum[0][j]);
            if(pq.size() > k) pq.pop();
        }

        for(int i = 1; i < m; i++){
            for(int j = 1; j < n; j++){
                presum[i][j] = presum[i-1][j] ^ presum[i][j-1] ^ presum[i-1][j-1] ^ matrix[i][j];
                pq.push(presum[i][j]);
                if(pq.size() > k) pq.pop();
            }
        }

        int res = pq.top();

        return res;

    }
};

/*
給你一個x y座標 算出在他之前包含他的XOR 找到第k大的那項數字
XOR -> 會越做越高嗎 -> NO
010 110 -> 2 XOR 6 -> 1 0 1 -> 5
2D presum -> presum[i][j] = presum[i-1][j] ^ presum[i][j-1] ^ matrix[i][j] ^ presum[i-1][j-1]
假設要做3*3這塊 先坐前面兩塊 會發現有一塊被XOR兩次等於變成0 在XOR回來 presum[i-1][j-1]
x x x 
x x x 
x x x
*/
