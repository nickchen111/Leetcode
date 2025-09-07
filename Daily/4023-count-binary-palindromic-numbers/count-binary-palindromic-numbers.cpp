class Solution {
public:
    long long makePalindrome(long long prefix, int len) {
        string s = bitset<50>(prefix).to_string();
        s = s.substr(s.find('1'));
        string t = s;
        if (len % 2 == 1) t.pop_back();
        reverse(t.begin(), t.end());
        s += t;
        return stoll(s, nullptr, 2);
    }

    long long countBinaryPalindromes(long long n) {
        if (n == 0) return 1;

        int len = 64 - __builtin_clzll(n);
        long long ans = 0;

        for (int L = 1; L < len; L++) {
            int half = (L + 1) / 2;
            ans += 1LL << (half - 1); 
        }

        int half = (len + 1) / 2;
        long long prefix = n >> (len - half);
        long long base = 1LL << (half - 1);

        if (prefix > base) ans += (prefix - base);

        long long pal = makePalindrome(prefix, len);
        if (pal <= n) ans++;

        return ans + 1;
    }
};