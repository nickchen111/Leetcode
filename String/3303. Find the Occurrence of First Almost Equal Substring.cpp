/*
3303. Find the Occurrence of First Almost Equal Substring
*/

// TC:O(nlgm + n + m) SC:O(n + m)
class Solution {
    using LL = long long;
public:
    int minStartingIndex(string s, string pattern) {
        int n = s.size();
        int m = pattern.size();
        vector<LL> power(n+1);
        power[0] = 1;
        LL base = 499;
        LL MOD = 1e9+7;
        
        vector<LL> hash1(n+1);
        vector<LL> hash2(m+1);
        
        for(int i = 0; i < n; i++){
            power[i+1] = (power[i]*base) % MOD;
            hash1[i+1] = (hash1[i]*base + (LL) s[i]) % MOD;
        }
        
        for(int i = 0; i < m; i++){
            hash2[i+1] = (hash2[i]*base + (LL) pattern[i]) % MOD;
        }
        // x x x x 
        
        auto sub_hash1 = [&](int l, int r){
            return ((hash1[r] - hash1[l] * power[r-l]) % MOD + MOD) % MOD;
        };
        
        auto sub_hash2 = [&](int l, int r){
            return ((hash2[r] - hash2[l] * power[r-l]) % MOD + MOD) % MOD;
        };
        
        
        for(int i = 0; i < n; i++){
            if(i + m - 1 >= n) return -1;
            if(sub_hash1(i, i+m) == sub_hash2(0, m)) return i;
            else {
                int bas = i;
                int left = 0, right = m;
                while(left < right){
                    int mid = left + (right - left)/2; // 假設這個是長度
                    
                    if(sub_hash1(bas, mid+bas) == sub_hash2(0, mid)) {
                        left = mid + 1;
                    }
                    else right = mid;
                }
                // x x x x x 
                if(sub_hash1(left+bas, bas+m) == sub_hash2(left, m)) return i;
            }
        }
        
        return -1;
        
        
    }
};
