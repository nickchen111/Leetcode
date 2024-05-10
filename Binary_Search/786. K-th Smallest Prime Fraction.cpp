/*
786. K-th Smallest Prime Fraction
*/

// 二分 TC:O(n*lgm) SC:O(1)
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& nums, int k) {
        int n = nums.size();
        double left = 0;
        double right = 1;
        double mid;
        while(left < right){
            mid = (left+right)/2;
            int count = 0;
            for(int i = 0; i < n; i++){
                auto pos = lower_bound(nums.begin(), nums.end(), nums[i]*1.0/mid);
                count += nums.end() - pos;
            }
            if(count < k){
                left = mid;
            }
            else if(count > k){
                right = mid;
            }
            else break;
        }
        vector<int> res(2);
        double ans = 0;
        for(int i = 0; i < n; i++){
            auto pos = lower_bound(nums.begin(), nums.end(), nums[i]*1.0/mid);
            int j = pos - nums.begin();
            if(pos != nums.end() && nums[i]*1.0/nums[j] > ans){
                ans = nums[i]*1.0/nums[j];
                res = {nums[i], nums[j]};
            }
        }

        return res;
    }
};

// PQ  TC:O(n^2+klg(n^2)) SC:O(n^2)
class Solution {
    using VD = vector<double>;
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        priority_queue<VD, vector<VD>, greater<VD>> pq;
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                pq.push({arr[i]*1.0/arr[j]*1.0, arr[i]*1.0,arr[j]*1.0});
            }
        }
        int count = k;
        vector<int> res(2);
        while(count--){
            res[0] = pq.top()[1];
            res[1] = pq.top()[2];
            pq.pop();
        }

        return res;

    }
};

/*
要找第k小的點-> PQ, 二分, multiset維護 三種方法 這題是用二分 因為可能性會需要遍歷n^2
這題的二分是兩邊都是開區間的離散點 所以不能用之前的mid+1 mid-1 要特別判斷跳出
然後再計算點的時候也要想好函式庫的二分該怎麼操作
nums[i]/nums[j] <= mid
nums[j] >= nums[i]/mid
*/
