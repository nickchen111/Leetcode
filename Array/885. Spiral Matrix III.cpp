/*
885. Spiral Matrix III
*/

// TC:O(m*n) SC:O(1)
class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart) {
        vector<vector<int>> res;

        int dirs = 0; // 0 right 1 down 2 left 3 up
        int count = 1;
        int step = 0;// 2 的倍數 就count++
        while(res.size() < rows*cols){
            if(rStart >= 0 && rStart < rows && cStart >= 0 && cStart < cols){
                res.push_back({rStart, cStart});
            }
            if(dirs == 0){
                int tmp = count-1;
                while(tmp--){
                    cStart += 1;
                    if(rStart >= 0 && rStart < rows && cStart >= 0 && cStart < cols){
                        res.push_back({rStart, cStart});
                    }
                }
                cStart += 1;
                dirs += 1;
            }
            else if(dirs == 1){
                int tmp = count-1;
                while(tmp--){
                    rStart += 1;
                    if(rStart >= 0 && rStart < rows && cStart >= 0 && cStart < cols){
                        res.push_back({rStart, cStart});
                    }
                }
                rStart += 1;
                dirs += 1;
                count += 1;
            }
            else if(dirs == 2){
                int tmp = count-1;
                while(tmp--){
                    cStart -= 1;
                    if(rStart >= 0 && rStart < rows && cStart >= 0 && cStart < cols){
                        res.push_back({rStart, cStart});
                    }
                }
                cStart -= 1;
                dirs += 1;
            }
            else {
                int tmp = count-1;
                while(tmp--){
                    rStart -= 1;
                    if(rStart >= 0 && rStart < rows && cStart >= 0 && cStart < cols){
                        res.push_back({rStart, cStart});
                    }
                }
                dirs = 0;
                rStart -= 1;
                count += 1;
            }
        }

        return res;
    }
};
