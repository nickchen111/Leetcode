// TC:O(n * sqrt(n)) SC:O(n)
class Solution {
public:
    bool divisorGame(int n) {
        vector<int> memo(n+1, -1);
        auto dfs = [&](auto &&dfs, int N) -> bool {
            if(N == 1) return false;
            if(memo[N] != -1) return memo[N];
            vector<int> prime = {1};
            for(int i = 2; i*i <= N; i++) {
                if((N % i) == 0) {
                    prime.emplace_back(i);
                    if(N / i != i) {
                        prime.emplace_back(N / i);
                    }
                }
            }
            bool flag = false;
            for(auto &p : prime) {
                flag |= (!dfs(dfs, N - p));
            }
            return memo[N] = flag;
        };
        return dfs(dfs, n);
    }
};

// Math TC:O(1) SC:O(1)
class Solution {
public:
    bool divisorGame(int n) {
        return n % 2 == 0;
    }
};
