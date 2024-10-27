/*
3334. Find the Maximum Factor Score of Array
*/

// TC:O(n*lgn) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maxScore(vector<int>& nums) {
        int n = nums.size();
       
        vector<LL> suffixg(n+1);
        vector<LL> suffixl(n+1,1);
        suffixg[n-1] = suffixl[n-1] = nums.back();
        
        for(int i = n-2; i >= 0; i--) {
            suffixg[i] = gcd(suffixg[i+1], nums[i]);
            suffixl[i] = ((LL)nums[i]*suffixl[i+1]) / gcd(suffixl[i+1], nums[i]);
        }
        
        LL preg = 0, prel = 1;
        LL res = suffixg[0]*suffixl[0];
        for(int i = 0; i < n; i++) {
            LL curg = gcd(preg, suffixg[i+1]);
            LL curl = lcm(prel, suffixl[i+1]);
            preg = gcd(preg, nums[i]);
            prel = prel*nums[i] / gcd(prel, nums[i]);
            // cout << curg << ' ' << curl;
            res = max(res, curg * curl);
        }
        
        return res;
    }
};


// TC:O(n^2*lgn) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long maxScore(vector<int>& nums) {
        int n = nums.size();
        LL g = nums[0];
        LL l = nums[0];
        for(int i = 1; i < n; i++) {
            g = gcd(g, nums[i]);
            l = (nums[i]*l) / gcd(l,nums[i]);
        }
       
        LL res = l*g;
        for(int i = 0; i < n; i++) {
            LL g1 = -1;
            LL l1 = -1;
            for(int j = 0; j < n; j++) {
                if(i == j) continue;
                if(g1 == -1) {
                    g1 = nums[j];
                    l1 = nums[j];
                }
                else {
                    g1 = gcd(g1, nums[j]);
                    l1 = (nums[j]*l1) / gcd(l1,nums[j]);
                }
            }
            res = max(res, l1*g1);
        }
        
        return res;
    }
};
