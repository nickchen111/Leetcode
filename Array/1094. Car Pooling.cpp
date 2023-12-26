/*
1094. Car Pooling
*/

// TC:O(n) SC:O(n) 12/26
class Solution {
    int diff[1002];
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        // diff
        int n = trips.size();
        for(auto &trip : trips){
            diff[trip[1]] += trip[0];
            diff[trip[2]] -= trip[0];
        }

        long long sum = 0;
        for(int i = 0; i <= 1000; i++){
            sum += diff[i];
            if(sum > capacity) return false;
        }

        return true;
    }
};

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        vector<int> nums(1001, 0);
        Difference df(nums);//構造差分數組

        for(auto trip: trips){
            int val = trip[0];
            int i = trip[1];
            int j = trip[2]-1;
            df.increment(i, j, val);
        }

        vector<int> ans = df.result();

        for(int i = 0; i < ans.size(); i++){
            if(ans[i] > capacity) return false;
        }

        return true;
    }
private:
    class Difference {
        vector<int> diff;
    public:
        Difference(vector<int>& nums){
            assert(nums.size() > 0);
            diff = vector<int>(nums.size(), 0);
            diff[0] = nums[0];

            for(int i = 1; i < nums.size(); i++){
                diff[i] = nums[i] - nums[i-1];
            }
        }
    
        void increment(int i, int j, int val){
            diff[i] +=val;
            if(j+1 < diff.size()){
                diff[j+1] -= val;
            }
        }

        vector<int> result(){//利用差分數組構建回更動後的數組
            vector<int> ans(diff.size(), 0);
            ans[0] = diff[0];
            for(int i = 1; i < diff.size(); i++){
                ans[i] = ans[i-1] + diff[i];
            }

            return ans;
        }
    };
};

/*
解題思路：
此題也是一差分數組題
細節在於：
trips[i] 代表着一组区间操作，旅客的上车和下车就相当于数组的区间加减；只要结果数组中的元素都小于 capacity，就说明可以不超载运输所有旅客。
这题还有一个细节，一批乘客从站点 trip[1] 上车，到站点 trip[2] 下车，呆在车上的站点应该是 [trip[1], trip[2] - 1]，这是需要被操作的索引区
间。
0 <= fromi < toi <= 1000 站點數最多為1001個
tc: o(n) 其實也可看作o(1) sc: o(1) 因為此題固定長度了
*/
