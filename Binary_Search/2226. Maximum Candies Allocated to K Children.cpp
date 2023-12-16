/*
2226. Maximum Candies Allocated to K Children
*/


// TC:O(n*lgmax) SC:O(1)
class Solution {
    using LL = long long;
public:
    int maximumCandies(vector<int>& candies, long long k) {
       
        LL low = 0; LL high = 1e7; //分配的糖果數量
        while(low < high){
            LL mid = low + (high - low + 1) / 2;
            //可以分配給這麼多小孩的話
            if(solve(candies, k, mid)) low = mid;
            else high = mid-1;
        }

        return high;
    }

    bool solve(vector<int>& candies, long long k,  LL num){
        LL sum = 0;
        for(int i = 0; i < candies.size(); i++){
            sum = sum + (LL)candies[i]/num;
        }

        return sum >= k;
    }
};

/*
給你一數組內含很多堆糖果 每一推的數量為他的value 你可以將每一堆拆成好多堆
問說每一個小孩拿到糖果數量要一樣並且他們最多只能拿一堆 最多可以分配幾個糖果
小孩越多 能分配到的糖果數量越少 單調性 -> Binary Search
*/
