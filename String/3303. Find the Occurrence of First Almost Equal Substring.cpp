/*
3303. Find the Occurrence of First Almost Equal Substring
*/


// Z function 好懂版 TC:O(n) SC:O(n)
class Solution {
public:
    int minStartingIndex(string s, string pattern) {
        int m = s.size();
        int n = pattern.size();
        // 預處理pattern的z function
        auto cal_z = [&](string& t) -> vector<int> {
            vector<int> z(n);
            z[0] = n;
            for(int i = 1, c = 1, r = 1, len; i < n; i++) {
                len = r > i ? min(z[i-c], r-i) : 0;
                while(i + len < n && t[len] == t[i+len]) {
                    len ++;
                }
                if(i + len > r) {
                    r = i + len;
                    c = i;
                }
                z[i] = len;
            }

            return z;
        };

        vector<int> z1 = cal_z(pattern);
        string t = pattern;
        reverse(t.begin(), t.end());
        vector<int> z2 = cal_z(t);

        auto cal_e = [&](string& s, vector<int>& z, string& t) -> vector<int> {
            vector<int> e(m);
            for(int i = 0, c = 0, r = 0, len; i < m; i++) {
                len = r > i ? min(z[i-c], r-i) : 0;
                while(i + len < m && t[len] == s[i + len]) {
                    len ++;
                }
                if(i + len > r) {
                    r = i + len;
                    c = i;
                }
                e[i] = len;
            } 
            return e;
        };

        vector<int> prefix = cal_e(s, z1, pattern);

        string p = s;
        reverse(p.begin(), p.end());
        vector<int> suffix = cal_e(p, z2, t);
        reverse(suffix.begin(), suffix.end());

        for(int i = 0; i < m; i++) {
            if(i+n-1 < m && prefix[i] + suffix[i+n-1] >= n-1) return i;
        }

        return -1;
    
    }
};

// Z function TC:O(n) SC:O(n)
class Solution {
    vector<int> cal_z(string s){
        int n = s.size();
        int box_l = 0, box_r = 0;
        vector<int> z(n);
        for(int i = 1; i < n; i++){
            if(i <= box_r){
                z[i] = min(z[i-box_l], box_r - i + 1);
            }

            while(i + z[i] < n && s[z[i]] == s[z[i]+i]){
                box_l = i;
                box_r = z[i]+i;
                z[i]++;
            }
        }

        return z;
    }
public:
    int minStartingIndex(string s, string pattern) {
        vector<int> prefix_z = cal_z(pattern + s);
        reverse(s.begin(), s.end());
        reverse(pattern.begin(), pattern.end());

        vector<int> suffix_z = cal_z(pattern + s);
        
        int m = pattern.size();
        int n = s.size();
        int t = suffix_z.size();
        // 5 + 4 = x x x x  (O O) O O O
        for(int i = m; i <= n; i++){
            // -1 代表的是目前這個字可更改所以加入的長度
            if(prefix_z[i] + suffix_z[t-1-i+1] >= m-1){
                return i - m;
            }
        }

        return -1;
    }
};

// 字符串哈希 + 二分 TC:O(nlgm + n + m) SC:O(n + m)
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
