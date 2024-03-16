/*
3079. Find the Sum of Encrypted Integers
*/

// TC:O(m*n) m為數組長度  n為字串長度 最長4 SC:O(1)
class Solution {
public:
    int sumOfEncryptedInt(vector<int>& nums) {
        int sum = 0;
        for(auto x : nums){
            string cur = to_string(x);
            int n = cur.size();
            char ch = cur[0];
            for(int i = 1; i < cur.size(); i++){
                if(cur[i] > ch) {
                    ch = cur[i];
                }
            }
            
            for(int i = 0; i < cur.size(); i++){
                cur[i] = ch;
            }
            
            sum += stoi(cur);
        }
        
        return sum;
    }
};
