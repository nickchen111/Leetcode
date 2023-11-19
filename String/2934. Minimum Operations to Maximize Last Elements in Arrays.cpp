/*
2934. Minimum Operations to Maximize Last Elements in Arrays
*/

// TC:O(nlgn+n) SC:O(1)
class Solution {
public:
    long long minimumSteps(string s) {
        long long res = 0;
        int n = s.size();
        string t=s;
        sort(t.begin(),t.end());
        if(t == s) return 0;
        //數每個1後面有多少個0
        //101000111001
        int count = 0;
        for(int i = n-1; i>=0; i--){
            if(s[i] == '0'){
                count+=1;
            }
            else if(s[i] == '1'){
                res+=count;
            }
        }
        
        return res;
       
    }
};
