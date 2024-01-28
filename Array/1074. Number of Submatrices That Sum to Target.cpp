/*
1074. Number of Submatrices That Sum to Target
*/

// TC:O(m*m*n*n) SC:O(n)
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int count = 0;
        for(int i = 0; i < m; i++){
            vector<int> temp(n);
            for(int j = i; j < m; j++){
                for(int t = 0; t < n; t++){
                    temp[t] += matrix[j][t];
                }
                count += helper(temp,target);
            }
        }

        return count;
    }
    int helper(vector<int>& temp, int target){
        int n = temp.size();
        int presum = 0;
        unordered_map<int,int> map;
        map[0] += 1;
        int res = 0;
        for(int i = 0; i < n; i++){
            presum += temp[i];
            if(map.find(presum-target) != map.end()) res += map[presum-target];
            map[presum] += 1;
        }

        return res;
    }
};


/*
此題與363題一樣做法 要想到一維矩陣會怎麼做 
就會想到要壓縮二維變一維 重點在固定上界與下界 然後用一個數組去紀錄當下上下界的presum即可
求每種可以累加到target的矩陣總和數量
x x x x 
x x x x 
x x x x 
x x x x 

*/
