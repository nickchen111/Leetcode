/*
3075. Maximize Happiness of Selected Children
*/

// TC:O(nlgn) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        LL sum = 0;
        LL count = 0;
        
        sort(happiness.rbegin(), happiness.rend());
        for(int i = 0; i < k; i++){
            if(happiness[i]-count < 0) break;
            sum = sum + happiness[i]-count;
            count++;
        }
        
        return sum;
    }
};

/*
可以選k個children 每一輪沒有被選到的都要減一問最後可以得到sum是多少
*/
