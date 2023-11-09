/*
1759. Count Number of Homogenous Substrings
*/

// TC:O(n) SC:O(1)
class Solution {
    long long M = 1e9+7;
public:
    int countHomogenous(string s) {
        // Hash table
        long long res = 0;
        int n=s.size();
        
        int count = 1;
        int i = 0;
        for(int j = 0; j<n; j++){
            if(s[i] == s[j]){
                res+=j-i+1;
            }
            else{
                res+=1;
                i = j;
            }
        }

        return res%M;
    }
};
