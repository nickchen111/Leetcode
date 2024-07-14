/*
3219. Minimum Cost for Cutting Cake II
*/

// TC:O(mlgm+nlgn + m+n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {
        m = horizontalCut.size();
        n = verticalCut.size();
        sort(horizontalCut.rbegin(), horizontalCut.rend());
        sort(verticalCut.rbegin(), verticalCut.rend());
        int count_h = 1;
        int count_v = 1;

        LL res = 0;
        int i = 0, j = 0;
        while(i < m && j < n){
            if(horizontalCut[i] > verticalCut[j]){
                res += (LL)horizontalCut[i]*count_v;
                count_h += 1;
                i++;
            }
            else {
                res += (LL)verticalCut[j]*count_h;
                count_v += 1;
                j++;
            }
        }
        
        while(i < m){
            res += (LL)horizontalCut[i]*count_v;
            i++;
        }
        
        while(j < n){
            res += (LL)verticalCut[j]*count_h;
            j++;
        }
        
        return res;
    }
};
