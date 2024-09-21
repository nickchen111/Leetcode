/*
30. Substring with Concatenation of All Words
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = s.size();
        vector<LL> power(n+1);
        vector<LL> hash(n+1);
        power[0] = 1;
        const LL MOD = 1e9+7;
        
        // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        // const LL base = uniform_int_distribution<>(8e8, 9e8)(rng); // 随幾 base，防止 hack
        
        const LL base = 499; 

        for(int i = 0; i < n; i++){
            power[i+1] = (power[i] * base) % MOD;
            hash[i+1] = (hash[i] * base + (LL)s[i]) % MOD;
        }

        auto sub_hash = [&](int l, int r){
            return ((hash[r] - hash[l] * power[r-l]) % MOD + MOD) % MOD;
        };

        unordered_map<LL,int> need;
        for(auto &w : words){
            LL sum = 0;
            for(int j = 0; j < w.size(); j++){
                sum = (sum*base + (LL)w[j]) % MOD;
            }

            need[sum] += 1;
        }

        int m = words[0].size(); // 每個字的長度
        int k = words.size(); // 多少個字
        vector<int> res;
        for(int t = 0; t < m; t++){
            unordered_map<LL,int> map;
            int i = t;
            int count = 0;
            for(int j = t; j < n; j += m){
                if(j + m > n) break;

                LL cur = sub_hash(j, j + m);
                if(need.find(cur) != need.end()){
                    map[cur] += 1;
                    if(map[cur] == need[cur]) {
                        count += 1;
                    }
                }

                if(j+m-i == m*k){

                    if(count == need.size()){
                        res.push_back(i);
                    }
                    
                    LL del = sub_hash(i, i + m);
                    if(need.find(del) != need.end()){
                        if(need[del] == map[del]){
                            count -= 1;
                        }
                        map[del] -= 1;
                    }

                    i += m;
                }
            }
        }

        return res;
    }
};
