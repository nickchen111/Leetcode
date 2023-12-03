/*
2951. Find the Peaks
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> findPeaks(vector<int>& mountain) {
        int n = mountain.size();
        vector<int> res;
        for(int i = 1; i < n-1; i++){
            if(mountain[i] > mountain[i-1] && mountain[i+1] < mountain[i]){
                res.push_back(i);
            }
        }
        
        return res;
    }
};
