/*
2875. Minimum Size Subarray in Infinite Array
*/

// Slide Window TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    int minSizeSubarray(vector<int>& nums, int target) {
        int n = nums.size();
        LL total = reduce(nums.begin(), nums.end(), 0LL);
        int i = 0;
        LL sum = 0;
        int len = INT_MAX/2;
        for(int j = 0; j < 2*n; j++) {
            sum += (LL)nums[j%n];
            while(sum > target % total) {
                sum -= (LL)nums[i%n];
                i++;
            }
            if(sum == target % total) {
                len = min(len, j - i + 1);
            }
        }

        if(len == INT_MAX/2) return -1;
        return len + target / total * n;
    }
};

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    int minSizeSubarray(vector<int>& nums, int target) {
        LL total = accumulate(nums.begin(),nums.end(),0LL);
        int n = nums.size();
        for(int i = 0; i<n; i++){
            nums.push_back(nums[i]);
        }
        
        vector<LL> presum(2*n);
        presum[0] = nums[0];
        for(int i =1; i<2*n; i++){
            presum[i] = presum[i-1]+nums[i];
        }

        unordered_map<LL, int> map; // 餘數->index
        LL res = INT_MAX/2;
        map[0] = -1;
        for(int i = 0; i<2*n; i++){
            LL r = ((presum[i]-target)%total+total)%total;
            if(map.find(r) != map.end()){
                LL j = map[r];
                LL k = ((j == -1 ? 0:presum[j])-presum[i]+target)/total;
                res = min(res,i-j+k*n);

            }
            map[presum[i]%total] = i;
        }

        if(res == INT_MAX/2) return -1;
        else return res;

    }
};

/*
此題又有餘數的味道
讓他繞兩圈 其他的中間都可以用K*TOTAL取代
[x x x x x](....)(.....)(.....)[x x x x x]
       j.-------------------------i
presum[i] - presum[j] = target + k*total;
presum[j] = presum[i] - target + k*total;
i-j+k*n
兩邊的餘數相等就會是答案
*/
