/*
2961. Double Modular Exponentiation
*/

// TC:O(n*k) k 為平均冪次方次數 SC:O(1)
class Solution {
public:
    vector<int> getGoodIndices(vector<vector<int>>& variables, int target) {
        vector<int> res;
        for(int i = 0; i < variables.size(); i++){
            int a = variables[i][0], b = variables[i][1], c = variables[i][2], d = variables[i][3];
            //for 初始化第一個取模結果
            int n1 = 1;
            for(int j = 0; j < b; j++){
                n1 = (n1 * a) % 10;
            }

            int n2 = 1;
            for(int k = 0; k < c; k++){
                n2 = (n2 * n1) % d;
            }

            if(n2 == target) res.push_back(i);
        }

        return res;
    }
};

/*
此題目標
((aibi % 10)ci) % mi == target
主要是考驗如何對太大的數字取模 用快速冪是錯誤的 他只能幫我縮短時間 但沒辦法幫我正確取模
*/
