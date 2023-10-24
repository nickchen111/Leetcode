/*
1899. Merge Triplets to Form Target Triplet
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        int x = target[0];
        int y = target[1];
        int z = target[2];

        bool foundX = 0; bool foundY = 0; bool foundZ = 0;
        for(auto triplet:triplets){
            //皆要小於才可以抵達正確答案 因為每次的替換都會取最大值 取太大就沒救了
            if(triplet[0] <= x && triplet[1] <= y && triplet[2] <= z){
                if(triplet[0] == x) foundX = true;
                if(triplet[1] == y) foundY = true;
                if(triplet[2] == z) foundZ = true;
            }
            if (foundX && foundY && foundZ) return true;
        }

        return false;
    }
};

/*
要換一個字 最好的情況就是要找到比他小的 其他可以不管是否一樣但一定要比target小
*/
