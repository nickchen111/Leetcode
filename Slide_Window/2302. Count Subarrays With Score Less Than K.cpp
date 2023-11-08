/*
2302. Count Subarrays With Score Less Than K
*/

// Slide Window TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();

        LL sum = 0;
        LL res = 0;
        int i = 0;
        //固定右端點看左端點是否需移動
        for(int j =0; j<n; j++){
            sum+=nums[j];
            while(sum*(j-i+1) >= k){
                sum-=nums[i];
                i++;
            }
            res+=(j-i+1);
        }
        

        return res;
    }
};

// Binary Search + Presum TC:O(nlgn) SC:O(n)
class Solution {
    using LL = long long;
    vector<LL> presum; 
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        int n = nums.size();
        presum.resize(n+1);
        for(int i = 1; i<=n; i++){
            presum[i] = presum[i-1]+nums[i-1];
        }

        LL res = 0;
        for(int i = 0; i<n; i++){
            if(nums[i] >= k) continue;
            int left = 1; int right = i+1;//長度
            while(left < right){
                int mid = left+(right-left+1)/2;
                if((presum[i+1]-presum[i+1-mid])*mid < k){
                   left = mid;
                }
                else{
                   right = mid-1;
                }
            }
            
            res+=left;
        }

        return res;
    }
};

/*
二分想法:
這道題沒有辦法將元素當成某subarray的最大或者最小 
換種想法將它想成最後一個元素
會發現這是單調的 長度越長就會越大 那就是二分 猜一下長度
滑窗想法：
畢竟越往右走會越大那麽這題肯定也可以滑窗
*/
