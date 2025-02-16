// TC:O(2^n) SC:O(n)
class Solution {
public:
    vector<int> constructDistancedSequence(int n) {
        vector<bool> visited(n+1);
        vector<int> ans(n*2-1);
        auto backtrack = [&](auto &&backtrack, int pos) -> bool {
            if(pos >= ans.size()) return true;
            if(ans[pos] != 0) return backtrack(backtrack, pos+1);
            for(int i = n; i >= 1; i--) {
                if(visited[i]) continue;
                if(i == 1) {
                    visited[i] = true;
                    ans[pos] = i;
                    if(backtrack(backtrack, pos+1)) return true;
                    visited[i] = false;
                    ans[pos] = 0;
                    return false;
                }
                else {
                    if(i + pos >= ans.size() || ans[i + pos]) continue;
                    visited[i] = true;
                    ans[pos] = i, ans[i + pos] = i;
                    if(backtrack(backtrack, pos+1)) return true;
                    visited[i] = false;
                    ans[pos] = 0, ans[i + pos] = 0;
                }
            }
            return false;
        };
        backtrack(backtrack, 0);
        return ans;
    }
};
