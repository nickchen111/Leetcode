/*
2485. Find the Pivot Integer
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int pivotInteger(int n) {
        vector<int> presum(n+1);
        for(int i = 1; i <= n; i++){
            presum[i] = presum[i-1] + i;
        }

        for(int i = 1; i <= n; i++){
            if(presum[i] == presum[n] - presum[i-1]){
                return i;
            }
        }

        return -1;
    }
};
