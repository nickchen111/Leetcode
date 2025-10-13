// TC:O(n) SC:O(n)
class Solution {
public:
    int longestBalanced(string s) {
        /*
        前綴和? abc, ab, bc, ac, aaa, bbb, ccc
        考慮這幾種情況 求出最長前綴和
        */
        int n = s.size();
        int ans = 0;

        // 第一種情況都是a or b or c
        int i = 0;
        while (i < n) {
            int start = i + 1;
            while (start < n && s[start] == s[i]) start += 1;
            ans = max(ans, start - i);
            i = start;
        }
        auto f2 = [&](char x, char y) -> void {
            // x, y 表示 這次要收集的字母
            int i = 0, d = 0;
            while (i < n) {
                unordered_map<int, int> pos;
                pos[0] = i - 1;
                int d = 0;
                while (i < n && s[i] == x || s[i] == y) {
                    d += s[i] == x ? 1 : -1;
                    if (pos.count(d)) ans = max(ans, i - pos[d]);
                    else pos[d] = i;
                    i += 1;
                }
                i += 1;
            }
        };
        f2('a', 'b');
        f2('a', 'c');
        f2('b', 'c');

        unordered_map<long long, int> pos;
        pos[1LL * n << 32 | n] = -1;
        int cnt[3]{};
        for (int i = 0; i < n; i++) {
            cnt[s[i] - 'a'] += 1;
            long long p = 1LL * (cnt[0] - cnt[1] + n) << 32 | (cnt[1] - cnt[2] + n);
            if (pos.count(p)) ans = max(ans, i - pos[p]);
            else pos[p] = i;
        }

        return ans;
    }
};
