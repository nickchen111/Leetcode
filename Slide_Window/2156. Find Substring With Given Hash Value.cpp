// TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    string subStrHash(string s, int power, int modulo, int k, int hashValue) {
        LL pk = 1;
        LL hash = 0;
        int n = s.size();
        LL sum = 0;
        // x x x x x x n = 6 , k = 2
        for(int i = n - 1; i >= n - k; i--) {
            hash = ((hash * power) + s[i] - 'a' + 1) % modulo;
            pk = (pk * power) % modulo;
        }
        int ans = hash == hashValue ? n - k : 0;
        for(int i = n - k - 1; i >= 0; i--) {
            hash = (hash * power + (s[i] - 'a' + 1) - pk * (s[i+k] - 'a' + 1) % modulo + modulo) % modulo;
            if(hash == hashValue) ans = i;
        }

        return s.substr(ans, k);
    }
};
