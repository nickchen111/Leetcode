/*
1310. XOR Queries of a Subarray
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int n = queries.size();
        int m = arr.size();
        vector<LL> presum(m);
        LL sum = 0;
        for(int i = 0; i < m; i++){
            presum[i] = (i-1 < 0 ? 0 : presum[i-1]) ^ (LL)arr[i];
        }

        vector<int> res(n);
        for(int i = 0; i < n; i++){
            int a = queries[i][0], b = queries[i][1];
            res[i] = presum[b] ^ (a-1 < 0 ? 0 : presum[a-1]);
        }

        return res;
    }
};

/*
XOR
相同為0 不同為1
101 ^ 101 = 000
*/
