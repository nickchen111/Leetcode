/*
3226. Number of Bit Changes to Make Two Integers Equal
*/

// TC:O(m+n) SC:O(m+n)
class Solution {
public:
    int minChanges(int n, int k) {
        string s1;
        string s2;
        while(n){
            if(n & 1){
                s1 += '1';
            }
            else s1 += '0';
            n /= 2;
        }
        
        while(k){
            if(k & 1){
                s2 += '1';
            }
            else s2 += '0';
            k /= 2;
        }
        
        int res = 0;
        
        int m = s1.size();
        int t = s2.size();
        for(int i = 0; i < m; i++){
            if(i < t && s1[i] == '0' && s2[i] == '1') return -1;
            if(i < t && s1[i] == '1' && s2[i] == '0') res += 1;
            
            if(i >= t && s1[i] == '1') res += 1;
        }
        
        while(m < t){
            if(s2[m] == '1') return -1;
            m++;
        }
        
        return res;
    }
};
