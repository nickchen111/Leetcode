/*
1894. Find the Student that Will Replace the Chalk
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        LL sum = accumulate(chalk.begin(), chalk.end(), 0LL);
        k %= sum;
        int n = chalk.size();
        vector<LL> presum(n);
        presum[0] = chalk[0];
        for(int i = 1; i < n; i++){
            presum[i] = presum[i-1] + chalk[i];
        }

        auto iter = upper_bound(presum.begin(), presum.end(), k);
        // x x x x x 
        int res = iter - presum.begin();
        return res;
    }
};
