/*
3019. Number of Changing Keys
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int countKeyChanges(string s) {
        int n = s.size();
        int count = 0;
        int prev = s[0];
        for(int i = 1; i < n; i++){
            if(s[i] >= 'A' && s[i] <= 'Z'){
                if(s[i] != prev && s[i]+32 != prev) count += 1;
            }
            if(s[i] >= 'a' && s[i] <= 'z'){
                if(s[i] != prev && s[i]-32 != prev) count += 1;
            }
            prev = s[i];
        }
        
        return count;
    }
};
