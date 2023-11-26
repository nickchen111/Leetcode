/*
1727. Largest Submatrix With Rearrangements
*/

// TC:O(m*n+nlgn+n) SC:O(n)
class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        //與85題相似
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> graph(n,0);
        int res = 0;
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(matrix[i][j]==1) graph[j]+=1;
                else graph[j] = 0;
            }
            vector<int> histogram = graph;
            sort(histogram.begin(),histogram.end());
            res = max(res, calculateArea(histogram));
        }

        return res;
    }

    int calculateArea(vector<int>& histo){
        int n = histo.size();
        int res = 0;
        for(int i =0; i<histo.size(); i++){
            int h = histo[i];
            int w = n-i;
            res = max(res,h*w);
        }

        return res;
    }
};
