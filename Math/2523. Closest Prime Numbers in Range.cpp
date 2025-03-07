// TC:O(nlglgn) SC:O(m)
class Solution {
public:
    vector<int> closestPrimes(int left, int right) {
        auto Prime = [&](int n) -> vector<int> {
            vector<int> a(n+1);
            for(int i = 2; i * i <= n; i++) {
                if(a[i] == 0) {
                    int j = i * i;
                    while(j <= n) {
                        a[j] = 1;
                        j += i;
                    }
                }
            }
            vector<int> ans;
            for(int i = max(2, left); i <= n; i++) {
                if(a[i] == 0) ans.emplace_back(i);
            }
            return ans;
        };
        vector<int> prime = Prime(right);
        if(prime.size() < 2) return {-1, -1};
        int diff = INT_MAX;
        vector<int> ans{-1,-1};
        for(int i = 1; i < prime.size(); i++) {
            if(prime[i] - prime[i-1] < diff) {
                ans = {prime[i-1], prime[i]};
                diff = prime[i] - prime[i-1];
            }
        }
        return ans;
    }
};
