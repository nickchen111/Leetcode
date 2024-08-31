/*
3271. Hash Divided String
*/


// TC:O(n) SC:O(m) m = n/k
class Solution {
public:
    string stringHash(string s, int k) {
        int n = s.size();
        string res;
       // x x x x 
        for(int i = 0; i < n; i+=k){
            int sum = 0;
            for(int j = i; j < i+k; j++){
                sum = (sum + (s[j]-'a')) % 26;
            }
            res.push_back(sum+'a');
        }
        
        return res;
    }
};
