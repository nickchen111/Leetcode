/*
2681. Power of Heroes
*/

// TC:O(nlgn + n) SC:O(1)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int sumOfPower(vector<int>& nums) {
        //此題是求subsequence
        int n = nums.size();
        sort(nums.begin(),nums.end());

        LL sum = 0;
        LL res = 0;
        for(int i = 0; i<n; i++){
            LL square = (LL)nums[i]*(LL)nums[i]%M;
            if(i >=1)
                sum = (sum*2+nums[i-1])%M;
            res+= sum*square%M + (LL)nums[i]*square%M;
            res%=M;
        }

        return res;
    }
};

/*
此題是數組類型的求subsequence的題型 先排序好方便找哪些數字比當前選中的數字小
然後從這些比他小的可能中去找出越來越小的話之規律

X Y Z i x x x 

Z:(nums[i])^2 * nums[z]->2^0
Y:(nums[i])^2 * nums[Y]*pow(2,i-(Y)-1)->2^1
Z:(nums[i])^2 * nums[X]*pow(2,2)->2^2
多一個w
X Y Z W i ...
w 2^0
z 2^1
y 2^2
x 2^3
sum = sum*2+w;
res+= sum*nums[i]^2+nums[i]*nums[i]^2
*/
