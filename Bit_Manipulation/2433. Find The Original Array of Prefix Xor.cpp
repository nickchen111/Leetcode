/*
2433. Find The Original Array of Prefix Xor
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> findArray(vector<int>& pref) {
        //前綴和的概念去做
        int n = pref.size();
        vector<int> res(n);
        res[0] = pref[0];
        int pref_xor = 0;
        for(int i = 1; i<n; i++){
            pref_xor ^= res[i-1];
            res[i] = pref_xor^pref[i];
        }

        return res;
    }
};

/* 
pref[i] = res[i]^res[i-1] 5^7= 2    101  111-> 010 if 010^101 ->111 即 c = a^b a = b^c 
即 res[i] = res[0]^res[1]...^res[i-1]^pref[i]
*/
