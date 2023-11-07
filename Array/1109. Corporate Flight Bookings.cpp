/*
1109. Corporate Flight Bookings
*/

// TC: O(n) SC: O(n) 11/7
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> diff(n+2,0);

        for(int i = 0; i<bookings.size(); i++){
            diff[bookings[i][0]]+=bookings[i][2];
            diff[bookings[i][1]+1]-=bookings[i][2];
        }
        vector<int> res;
        int total = 0;
        for(int i = 1; i<=n; i++){
            total+=diff[i];
            res.push_back(total);
        }

        return res;
    }
};

//La
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> nums(n, 0);// 初始化題目要求的數組
        Difference df(nums);//建立差分數組
        for(auto booking:bookings){
            int i = booking[0]-1; //因為題目給的是1~n
            int j = booking[1]-1;
            int val = booking[2];

            df.increment(i, j, val);
        }

        return df.result();
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
解題思維：
跟370一樣套路 要用差分數組去得出各區間加加減減的結果
很多眉角要注意 需畫出原數組 差分->變化 更新後數組 會比較清楚之間的加加減減
tc: o(n) sc: o(n)
*/
