/*
3361. Shift Distance Between Two Strings
*/

// TC:O(26^3 + n) SC:O(26^2)
class Solution {
    using LL = long long;
public:
    long long shiftDistance(string s, string t, vector<int>& nextCost, vector<int>& previousCost) {
        int n = s.size();
        vector<vector<LL>> minDist(26, vector<LL>(26, LLONG_MAX / 3));
        
        for (int i = 0; i < 26; i++) {
            minDist[i][i] = 0;
        }
        
        LL next_total = accumulate(nextCost.begin(), nextCost.end(), 0LL);
        LL prev_total = accumulate(previousCost.begin(), previousCost.end(), 0LL);

        for (int i = 0; i < 26; i++) {
            int next = (i + 1) % 26;
            int prev = (i - 1 + 26) % 26;
            minDist[i][next] = min(static_cast<LL>(nextCost[i]), prev_total - previousCost[next]);
            minDist[i][prev] = min(static_cast<LL>(previousCost[i]), next_total - nextCost[prev]);
        }

        for (int k = 0; k < 26; k++) {
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    minDist[i][j] = min(minDist[i][j], minDist[i][k] + minDist[k][j]);
                }
            }
        }

        LL res = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != t[i]) {
                res += minDist[s[i] - 'a'][t[i] - 'a'];
            }
        }
        
        return res;
    }
};
