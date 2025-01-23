/*
1574. Shortest Subarray to be Removed to Make Array Sorted
*/

// 2025.01.23 同向雙指針 TC:O(n) SC:O(1)
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = n-1;
        while(left+1 < n) {
            if(nums[left] <= nums[left+1]) left += 1;
            else break;
        }
        while(right - 1 >= 0) {
            if(nums[right-1] <= nums[right]) right -= 1;
            else break;
        }
        if(left >= right) return 0;
        // 目前各自停在自己的最大left 最小right點
        if(nums[left] <= nums[right]) return right - left - 1;
        int base = right - left - 1;
        // 先嘗試移動left 讓他能夠容納
        int ans = min(left + 1, n - right) + base;
        int i = 0, j = right;
        while(i <= left && j < n) {
            if(nums[i] <= nums[j]) {
                ans = min(ans, base + left - i + j - right);
                i += 1;
            }
            else {
                j += 1;
            }
        }
        return ans;
    }
};

// Two Pointer TC:O(n) SC:O(1)
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        int res = n-1;

        //[j:n-1]區間check
        int j = n-1;
        while(j-1 >= 0 && arr[j] >= arr[j-1]){
            j--;
        }

        res = min(res,j);
        if(res == 0) return 0;

        
        // [0:i] 區間check
        for(int i = 0; i < n; i++){
            if(i-1 >= 0 && arr[i] < arr[i-1]) break;
            while(j < n && arr[j] < arr[i]) j++;
            res = min(res, j-i-1);
        }

        return res;

    }
};


// BS 2024.11.15 好理解
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();

        // 預處理
        vector<int> suffix(n, 1);
        vector<int> prefix(n, 1);

        for(int i = n - 2; i >= 0; --i) {
            if (arr[i] <= arr[i + 1]) {
                suffix[i] = suffix[i + 1] + 1;
            }
        }

        for(int i = 1; i < n; ++i) {
            if (arr[i] >= arr[i - 1]) {
                prefix[i] = prefix[i - 1] + 1;
            }
        }

        auto check = [&](int mid) -> bool {
            int l = 0, r = mid - 1;
            while (r < n) {
                if (l > 0 && r + 1 < n) {
                    if (prefix[l - 1] + suffix[r + 1] == n - mid && arr[l - 1] <= arr[r + 1]) {
                        return true;
                    }
                }
                else if (r + 1 < n) {
                    if (suffix[r + 1] == n - mid) {
                        return true;
                    }
                }
                else if (l > 0) {
                    if (prefix[l - 1] == n - mid) {
                        return true;
                    }
                }
                ++r;
                ++l;
            }
            return false;
        };

        int left = 0, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }

        return left;
    }
};



// Binary Search  TC:O(n*lgn) SC:O(1)
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        arr.insert(arr.begin(),INT_MIN);
        arr.push_back(INT_MAX);

        int L = 1;
        while(L <= n){
            if(arr[L] <= arr[L+1]) L++;
            else break;
        }

        int R = n;
        while(R >= 1){
            if(arr[R] >= arr[R-1]) R--;
            else break;
        }

        if(R < L) {
            return 0;
        }

        int T = R-L-1;//中間段是肯定要移除的
    
        int res = INT_MAX;

        for(int i = 0; i <= L; i++){
            auto iter = lower_bound(arr.begin()+R, arr.end(), arr[i]);
            
            int remove = (iter-(arr.begin()+R));
            res = min(res, T + remove + L-i);
        }

        return res;
    }
};


/*
這題問說最少要移除多少元素能讓整個數組變成有序的 此題跟週賽的2972題很像 2972是問說可以有多少種移除方法
Binary Search
L T R 三段去嘗試 R是必定要移除的段 L開始去二分找可以接上的R的點 
Two Pointer 作法
一樣區分 L T R 三區
1. [0:i] increase
2. [j:n-1] increase
3. arr[i] <= arr[j]
*/
