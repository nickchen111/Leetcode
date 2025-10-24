class Solution {
public:
    int nextBeautifulNumber(int n) {
        while (true) {
            n++;
            int cnt[10]{};
            for (int x = n; x > 0; x /= 10) {
                cnt[x % 10]++;
            }

            bool ok = true;
            for (int x = n; x > 0; x /= 10) {
                if (cnt[x % 10] != x % 10) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                return n;
            }
        }
    }
};
