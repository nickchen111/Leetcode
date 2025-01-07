// TC:O(nlng + n^2 * m) m =字串平均長度 SC:O(n * m)
class Solution {
    using LL = long long;
public:
    vector<string> stringMatching(vector<string>& words) {
        auto cmp = [](const string& a, const string& b) {
            return a.size() < b.size();
        };
        sort(words.begin(), words.end(),cmp);
        const LL MOD = 1e9 + 7;
        const LL base = 499;
        vector<LL> power(102);
        power[0] = 1;
        for (int i = 0; i < 101; i++) {
            power[i + 1] = (power[i] * base) % MOD;
        }

        int n = words.size();
        vector<vector<LL>> hash(n, vector<LL>(102));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < words[i].size(); j++) {
                hash[i][j + 1] = (hash[i][j] * base + (LL)words[i][j]) % MOD;
            }
        }

        auto sub_hash = [&](int idx, int l, int r) -> LL {
            return ((hash[idx][r] - hash[idx][l] * power[r - l]) % MOD + MOD) % MOD;
        };

        vector<string> ans;
        for (int i = 0; i < n; i++) {
            LL hash_val = hash[i][words[i].size()];
            bool flag = 0;
            for (int j = i+1; j < n; j++) {
                for (int k = 0; k <= words[j].size() - words[i].size(); k++) {
                    if (sub_hash(j, k, k + words[i].size()) == hash_val) {
                        ans.push_back(words[i]);
                        flag = 1;
                        break;
                    }
                }

                if (flag) break;
            }
        }

        return ans;
    }
};
