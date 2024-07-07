/*
3210. Find the Encrypted String
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    string getEncryptedString(string s, int k) {
        string res = s;
        int n = s.size();
        for(int i = 0; i < n; i++){
            int mod = (i+k) % n;
            res[i] = s[mod];
        }
        
        return res;
    }
};
