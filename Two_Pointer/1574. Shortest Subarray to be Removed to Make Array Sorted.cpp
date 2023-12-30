/*
1574. Shortest Subarray to be Removed to Make Array Sorted
*/

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
