/*
3292. Minimum Number of Valid Strings to Form Target II
*/

// TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    int minValidStrings(vector<string>& words, string target) {
        int n = target.size();
        // 字符串哈希 預處理 power, hash 數組
        const LL MOD = 1070777777;
        
        // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        // const int base = uniform_int_distribution<>(8e8, 9e8)(rng); // 随幾 base，防止 hack
        
        const LL base = 499; 
        vector<LL> hash(n+1);
        vector<LL> power(n+1);
        power[0] = 1;
        for(int i = 0; i < n; i++){
            power[i+1] = (power[i]*base) % MOD;
            hash[i+1] = (hash[i]*base + (LL) target[i]) % MOD;
        }

        // 計算區間hash的數值 區間是1 index
        auto sub_hash = [&](int l, int r){
            return ((hash[r] - hash[l] * power[r-l]) % MOD + MOD) % MOD;
        };

        int maxLen = 0;
        for(auto &w : words){
            maxLen = max(maxLen, (int)w.size());
        }

        vector<unordered_set<int>> set(maxLen);
        for(auto &w : words){
            LL sum = 0;
            for(int j = 0; j < w.size(); j++){
                sum = (sum*base + w[j]) % MOD;
                set[j].insert(sum);
            }
        }

        // 二分算出當下這點可以跳到多遠
        auto cal_sz = [&](int i) -> int {
            int left = 0, right = min(n - i, maxLen);
            while (left < right) {
                int mid = left + (right - left)/2;
                if(set[mid].find(sub_hash(i, mid+i+1)) != set[mid].end()){
                    left = mid + 1;
                }
                else right = mid;
            }

            return left;
        };

        int cur_r = 0;
        int nxt_r = 0;
        int step = 0;
        for(int i = 0; i < n; i++){
            int len = cal_sz(i);
            nxt_r = max(nxt_r, i + len);
            if(i == cur_r){
                if(i == nxt_r) return -1; // 當下的點之前無論如何無法建造下座橋到i+1
                cur_r = nxt_r;
                step += 1;
            }
        }

        return step;
    }
};
