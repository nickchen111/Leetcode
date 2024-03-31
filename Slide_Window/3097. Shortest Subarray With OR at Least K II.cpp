/*
3097. Shortest Subarray With OR at Least K II
*/

// 變動長度滑窗 TC:O(n) SC:O(1)
class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        
        
        vector<int> count(32);
        if(k == 0) return 1;
        int len = INT_MAX;
        int i = 0;
        int curVal = 0;
        for(int j = 0; j < n; j++){
            for(int k = 0; k < 32; k++){
                int tmp = (nums[j]>>k)&1;
                if(tmp) count[k] += 1; 
                if(count[k] == 1){
                    curVal |= (1<<k);
                }
            }
            
            while(i < n && curVal >= k){
                len = min(len, j-i+1);
                for(int k = 0; k < 32; k++){
                    if(!count[k]) continue;
                    int tmp = (nums[i]>>k)&1;
                    if(tmp){
                        count[k] -= 1;
                        if(count[k] == 0){
                            curVal -= (1<<k);
                        }
                    }
                }
                i++;
            }
        }
        
        return len == INT_MAX ? -1 : len;
    }
};

//次佳解Binary Search + 固定長度滑窗 TC:O(32*n) SC:O(1)
class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 1, right = n;
        while(left < right){
            int mid = left + (right-left)/2;
            if(check(mid, nums,k)){
                right = mid;
            }
            else left = mid+1;
        }
        if(check(left, nums, k) == false) return -1;
        return left;
    }
    bool check(int len, vector<int>& nums, int k){
        vector<int> count(31,0);
        int n = nums.size();
        for(int i = 0; i < len-1; i++){
            for(int j = 0; j < 31; j++){
                count[j] += ((nums[i]>>j)&1);
            }
        }

        for(int i = len-1; i < n; i++){
            for(int j = 0; j < 31; j++){
                count[j] += ((nums[i]>>j)&1);
            }
            int sum = 0;
            for(int j = 0; j < 31; j++){
                if(count[j]) sum += (1<<j); 
            }
            if(sum >= k) return true;

            for(int j = 0; j < 31; j++){
                count[j] -= (nums[i-len+1]>>j)&1;
            }
        }

        return false;
    }
};



