/*
3228. Maximum Number of Operations to Move Ones to the End
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int maxOperations(string s) {
        int n = s.size();
        int count = 0;
        int res = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == '1'){
                count += 1;
            }
            else {
                int j = i;
                while(j < n && s[j] == '0'){
                    j++;
                }
                
                res += count;
                i = j-1;
            }
        }
        
        return res;
        
    }
};
