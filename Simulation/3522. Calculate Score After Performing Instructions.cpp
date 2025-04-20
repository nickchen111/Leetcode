// TC:O(n) SC:O(n)
class Solution {
    using ll = long long;
public:
    long long calculateScore(vector<string>& instructions, vector<int>& values) {
        int n = instructions.size();
        ll ans = 0;
        // unordered_set<int> set;
        vector<bool> visited(n);
        int i = 0;
        while (true) {
            if (i < 0 || i >= n || visited[i]) break; //set.count(i)
            // set.insert(i);
            visited[i] = true;
            if (instructions[i][0] == 'a') {
                ans += values[i];
                i += 1;
            }
            else {
                i += values[i];
            }
        }
        return ans;
    }
};
