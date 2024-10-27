/*
3335. Total Characters in String After Transformations I
*/

// 更好的解法是DP 此題數據規模可以用模擬 TC:O(26*t + n + 26) SC:O(26)
class Solution {
    using LL = long long;
public:
    int lengthAfterTransformations(string s, int t) {
        const int MOD = 1e9 + 7;
        vector<int> count(26, 0);
        
        
        for (char c : s) {
            count[c - 'a']++;
        }
        
        for (int i = 0; i < t; i++) {
            vector<int> next(26, 0);
            LL ab_count = count[25];
            count[25] = 0;
            
            for (int j = 0; j < 25; j++) {
                next[j + 1] += count[j];
            }
            
            next[0] += ab_count; 
            next[1] += ab_count; 
            
            for (int j = 0; j < 26; j++) {
                count[j] = next[j] % MOD;
            }
        }
        
        LL total = 0;
        for (int cnt : count) {
            total = (total + cnt) % MOD;
        }
        
        return total;
    }
};

/*
a 要轉25次變成z 
26變 ab 看他可以轉幾次26次 就會生成多少長度
ex : 3次, 1 : ab -> b轉到25變ab
25變 zab
26變 abbc
...

z -> ab
ab -> bc
bc ->de
de -> ef ...
*/
