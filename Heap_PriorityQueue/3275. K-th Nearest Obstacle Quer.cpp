/*
3275. K-th Nearest Obstacle Quer
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> resultsArray(vector<vector<int>>& queries, int k) {
        int m = queries.size();
        vector<int> res(m,-1);
        priority_queue<int, vector<int>, less<int>> pq1;
        priority_queue<int, vector<int>, greater<int>> pq2;
        for(int i = 0; i < m; i++){
            int a = abs(queries[i][0]), b = abs(queries[i][1]);
            int sum = a + b;
            if(i >= k){
                if(sum < pq1.top()) {
                    int cur = pq1.top();
                    pq1.pop();
                    pq2.push(cur);
                    pq1.push(sum);
                }
                else {
                    pq2.push(sum);
                }
                res[i] = pq1.top();
            }
            else {
                pq1.push(sum);
                if(i == k-1) res[i] = pq1.top();
            }
        }
        
        return res;
    }
};
