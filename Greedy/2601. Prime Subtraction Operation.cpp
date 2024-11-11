/*
2601. Prime Subtraction Operation
*/

// TC:O(lglgU + n*lgm) m 為當下範圍質樹的數量 SC:O(m)
class Solution {
public:
    bool primeSubOperation(vector<int>& nums) {
        int n = nums.size();
        int maxVal = *max_element(nums.begin(), nums.end());
        function<vector<int>(int)> sieve = [&](int mx) {
            vector<bool> q(mx+1); // true就是非prime
            for(int i = 2; i <= sqrt(mx); i++) {
                if(q[i]) continue;
                int j = i*2;
                while(j <= mx) {
                    q[j] = 1;
                    j += i;
                }
            }
            vector<int> pri;
            for(int i =2; i <= mx; i++) {
                if(!q[i]) pri.push_back(i);
            }

            return pri;
        };
        vector<int> prime = sieve(maxVal);
        for(int i = n-2; i >= 0; i--) {
            if(nums[i] >= nums[i+1]) {
                int diff = nums[i] - nums[i+1];
                auto iter = upper_bound(prime.begin(), prime.end(), diff);
                if(iter == prime.end() || *iter >= nums[i]) return false;
                nums[i] -= *iter;
            } 
        }

        return true;
    }
};
