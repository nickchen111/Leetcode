/*
3115. Maximum Prime Difference
*/

// TC:O(nlglgn + m ) n = 100, m = 3*10^5 SC:(n)
class Solution {
    
    vector<int> Eratosthenes(int n){
        vector<int> q(n+1,0);
        for(int i = 2; i<=sqrt(n); i++){
            if(q[i] == 1) continue; // not prime
            int j = 2*i; 
            while(j<=n){
                q[j] = 1;
                j+=i;
            }
        }

        
        return q;
    }

public:
    int maximumPrimeDifference(vector<int>& nums) {
        int n = nums.size();
        vector<int> sieve = Eratosthenes(100);
        int minVal = -1;
        int maxVal = -1;
        for(int i = 0; i < n; i++){
            if(nums[i] != 1 && sieve[nums[i]] == 0 && minVal == -1){
                minVal = i;
                maxVal = i;
            }
            else if(nums[i] != 1 && sieve[nums[i]] == 0){
                maxVal = i;
            }
        }
        
        return maxVal - minVal;
    }
};
